// const ENDPOINT_URL = "";
// const ENDPOINT_URL = "http://192.168.1.1";
const ENDPOINT_URL = "http://192.168.8.100";
const ENDPOINT_TICKERS = "https://api.coingecko.com/api/v3";

const CONTENT_DASHBOARD = ".main > .content > .dashboard";
const CONTENT_NETWORK = ".main > .content > .network";
const CONTENT_TICKERS = ".main > .content > .tickers";
const CONTENT_SETUP = ".main > .content > .setup";

const SUBCONTENT_DASHBOARD = CONTENT_DASHBOARD + " > .sub-content";
const SUBCONTENT_TICKERS = CONTENT_TICKERS + " > .sub-content";

const NAV_BUTTON = ".nav-button";
const NAV_OPEN_BUTTON = ".nav-open-button";

const HEADER_TITLE = ".main > .header > .title";
const HEADER_TITLE_RIGHT = ".main > .header > .right";

const BTN_NETWORK_DISCONNECT = ".btn-network-disconnect";
const BTN_NETWORK_CONNECT = ".btn-network-connect";

const BTN_TICKER_ADD = ".btn-ticker-add";
const BTN_TICKER_REMOVE = ".btn-ticker-remove";

const INPUT_TICKERS_COIN = ".tickers .input-coin";
const INPUT_TICKERS_CURRENCY = ".tickers .input-currency";

const LIST_TICKERS_COINS = $(INPUT_TICKERS_COIN).immybox({choices: []});
const LIST_TICKERS_CURRENCIES = $(INPUT_TICKERS_CURRENCY).immybox({choices: []});

const EVENTS = {
    MENU_CHANGED: new CustomEvent("MENU_CHANGED", 
        {
            'detail': {
                menu: null
            }
        }
    )
}

/* MENU */
$(document).ready(function() {
    var currentMenu = "dashboard";

    function showMenu(menu) {
        if(EVENTS.MENU_CHANGED.detail.menu !== menu) {
            $(".main > .content ." + currentMenu).hide();
            $(".main > .content ." + menu).show();

            currentMenu = menu;
            
            EVENTS.MENU_CHANGED.detail.menu = menu;
            document.dispatchEvent(EVENTS.MENU_CHANGED);
        }
    }

    $(document).on("click", NAV_BUTTON, function() {
        if(!$(this).hasClass("disabled")) {
            const menu = $(this).attr("data-menu");

            showMenu(menu);
        }
    });

    var menuIsOpen = false;

    $(document).on("click", NAV_OPEN_BUTTON, function() {
        if(menuIsOpen) {
            $(".grid-container").css("grid-template-columns", "0px 1.8fr");
        }
        else {
            $(".grid-container").css("grid-template-columns", "100px 1.8fr");
        }

        menuIsOpen = !menuIsOpen;
    });
});

/* NETWORK */
$(document).ready(function() {
    function rssiToColor(rssi) {
        if(rssi >= -71) {
            return "green";
        }
        else if(rssi >= -81 && rssi <= -70) {
            return "yellow";
        }
        else if(rssi <= -80) {
            return "red";
        }
    }

    function showWifiNetworks() {
        $(CONTENT_NETWORK).html("");

        $.getJSON(ENDPOINT_URL + "/data/wifi/status", (response) => {
            if(response["status"] == "ok") {
                currentNetwork = response["message"]["ssid"];
    
                $.getJSON(ENDPOINT_URL + "/data/wifi/list", (response) => {
                    if(response["status"] == "ok") {
            
                        const networks = response["message"];
            
                        for(network of networks) {
                            var newNetwork = $('<div class="box"></div>');
                            newNetwork.text(network["ssid"]);

                            var actionButton = $('<a class="button dark-blue" data-ssid="' + network["ssid"] + '" href="#"></a>');

                            if(network["ssid"] == currentNetwork) {
                                actionButton.addClass("red-bg btn-network-disconnect");
                                actionButton.append('<i class="fas fa-times"></i>');
                            }
                            else {
                                actionButton.addClass("green-bg btn-network-connect");
                                actionButton.append('<i class="fas fa-check"></i>');
                            }
                            newNetwork.append(actionButton);

                            const signalColor = rssiToColor(network["rssi"]);
                            newNetwork.append('<a class="button ' + signalColor + '" href="#"><i class="fas fa-signal"></i></a>');

                            $(CONTENT_NETWORK).append(newNetwork);
                        }

                        $(HEADER_TITLE_RIGHT).html('Found ' + networks.length + " networks");
                    }
                });
            }
        });
    }

    $(document).on("click", BTN_NETWORK_CONNECT, function() {
        const ssid = $(this).attr("data-ssid");

        const password = prompt("Please enter the password for " + ssid + ":", "");
        if (password == null || password == "") {
            alert("Invalid password entered, request cancelled");
            return;
        }

        $.post(ENDPOINT_URL + "/data/wifi/connect", {ssid: ssid, password: password}, (response) => {
            showWifiNetworks();
        });
    });

    $(document).on("click", BTN_NETWORK_DISCONNECT, function() {
        const ssid = $(this).attr("data-ssid");

        $.post(INKTICKER_URL + "/data/wifi/disconnect", (response) => {
            showWifiNetworks();
        });
    });

    document.addEventListener('MENU_CHANGED', (event) => {
        if(event.detail.menu == "network") {
            $(HEADER_TITLE).html("Network");
            $(HEADER_TITLE_RIGHT).html('Searching <i class="fas fa-circle-notch fa-spin"></i>');
            showWifiNetworks();
        }
    });
});

/* TICKERS */
$(document).ready(function() {
    function getTickers() {
        if(LIST_TICKERS_COINS[0].options.choices.length == 0) {
            console.log("loaded")
            $.getJSON(ENDPOINT_TICKERS + "/coins/list", (response) => {
                for(coin of response) {
                    LIST_TICKERS_COINS[0].options.choices.push({text: coin["name"], value: coin["id"]});
                }
            });
        }

        if(LIST_TICKERS_CURRENCIES[0].options.choices.length == 0) {
            $.getJSON(ENDPOINT_TICKERS + "/simple/supported_vs_currencies", (response) => {
                for(currency of response) {
                    LIST_TICKERS_CURRENCIES[0].options.choices.push({text: currency.toUpperCase(), value: currency.toUpperCase()});
                }
            });
        }
    }

    function showTickers() {
        $(SUBCONTENT_TICKERS).html("");

        $.getJSON(ENDPOINT_URL + "/data/tickers/list", (response) => {
            if(response["status"] == "ok") {
                const tickers = response["message"];
            
                for(ticker of tickers) {
                    var newBox = $('<div class="box"></div>');
                    newBox.text(ticker["coin"] + " - " + ticker["currency"]);

                    var deleteButton = $('<a class="button dark-blue red-bg btn-ticker-remove" href="#"><i class="fas fa-trash"></i></a>');
                    deleteButton.attr("data-id", ticker["id"]);
                    deleteButton.attr("data-coin", ticker["coin"]);
                    deleteButton.attr("data-currency", ticker["currency"]);

                    newBox.append(deleteButton);

                    $(SUBCONTENT_TICKERS).append(newBox);
                }

                $(HEADER_TITLE_RIGHT).html('You have ' + tickers.length + " ticker(s)");
            }
        });
    }

    $(document).on("click", BTN_TICKER_REMOVE, function() {
        const id = $(this).attr("data-id");
        const currency = $(this).attr("data-currency");

        $.post(ENDPOINT_URL + "/data/tickers/remove", {id: id, currency: currency}, (response) => {
            showTickers();
        });
    });

    $(document).on("click", BTN_TICKER_ADD, function() {
        if(LIST_TICKERS_COINS[0].selectedChoice === null || LIST_TICKERS_CURRENCIES[0].selectedChoice === null) {
            alert("Please select a coin and currency");
            return;
        }

        const id = LIST_TICKERS_COINS[0].selectedChoice.value;
        const coin = LIST_TICKERS_COINS[0].selectedChoice.text;
        const currency = LIST_TICKERS_CURRENCIES[0].selectedChoice.value

        $.post(ENDPOINT_URL + "/data/tickers/add", {id: id, coin: coin, currency: currency}, (response) => {
            $(INPUT_TICKERS_COIN).val("");
            $(INPUT_TICKERS_CURRENCY).val("");
            showTickers();
        });
    });

    document.addEventListener('MENU_CHANGED', (event) => {
        if(event.detail.menu == "tickers") {
            $(HEADER_TITLE).html("Tickers");
            $(HEADER_TITLE_RIGHT).html('Getting data <i class="fas fa-circle-notch fa-spin"></i>');

            getTickers();
            showTickers();
        }
    });

    $('.tickers').sortable({
        items: ".box:not(.non-sortable)",
        start: function(event, ui) {
            $(this).attr('data-previndex', ui.item.index());
        },
        update: function(event, ui) {
            var from = $(this).attr('data-previndex');
            var to = ui.item.index();

            $(this).removeAttr('data-previndex');
                       
            $.post(ENDPOINT_URL + "/data/tickers/order", {from: from, to: to}, (response) => {
                console.log(response);
            });
        }
    });

    $(".tickers" ).disableSelection();
});

/* SETUP */
$(document).ready(function() {
    function showSetup() {
        $(CONTENT_SETUP).html("");
    }

    document.addEventListener('MENU_CHANGED', (event) => {
        if(event.detail.menu == "setup") {
            $(HEADER_TITLE).html("Setup");
            $(HEADER_TITLE_RIGHT).html('Getting data <i class="fas fa-circle-notch fa-spin"></i>');
            showSetup();
        }
    });
});

/* DASHBOARD */
$(document).ready(function() {
    document.addEventListener('MENU_CHANGED', (event) => {
        if(event.detail.menu == "dashboard") {
            $(HEADER_TITLE).html("Dashboard");
            $(HEADER_TITLE_RIGHT).html('');
        }
    });
});

/* INIT */
$.getJSON(ENDPOINT_URL + "/data/wifi/status", (response) => {
    if(response["status"] == "ok") {
        const message = response["message"];
        if(!message["internet"]) {
            $(SUBCONTENT_DASHBOARD).slideDown();
            return;
        }
        
        $( ".nav-button" ).removeClass("disabled");
    }
});


function myFunction() {
    document.getElementById("myDropdown").classList.toggle("show");
  }
  
function filterFunction() {
    var input, filter, ul, li, a, i;
    input = document.getElementById("myInput");
    filter = input.value.toUpperCase();
    div = document.getElementById("myDropdown");
    a = div.getElementsByTagName("a");
    for (i = 0; i < a.length; i++) {
        txtValue = a[i].textContent || a[i].innerText;
        if (txtValue.toUpperCase().indexOf(filter) > -1) {
            a[i].style.display = "";
        } else {
            a[i].style.display = "none";
        }
    }
}