// const ENDPOINT_URL = "";
// const ENDPOINT_URL = "http://192.168.1.1";
const ENDPOINT_URL = "http://192.168.8.100";

const CONTENT_NETWORK = ".main > .content > .network";
const CONTENT_TICKERS = ".main > .content > .tickers";

const NAV_BUTTON = ".nav-button";
const NAV_OPEN_BUTTON = ".nav-open-button";

const HEADER_TITLE = ".main > .header > .title";
const HEADER_TITLE_RIGHT = ".main > .header > .right";

const BTN_NETWORK_DISCONNECT = ".btn-network-disconnect";
const BTN_NETWORK_CONNECT = ".btn-network-connect";

const BTN_TICKER_ADD = ".btn-ticker-add";
const BTN_TICKER_REMOVE = ".btn-ticker-remove";

const EVENTS = {
    MENU_CHANGED: new CustomEvent("MENU_CHANGED", 
        {
            'detail': {
                menu: null
            }
        }
    )
}

$(document).ready(function() {
    var currentMenu = "tickers";

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
        const menu = $(this).attr("data-menu");

        showMenu(menu);
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


// function boxButton(classes, data, icon) {
//     return $('<a class="button ' + classes + '" ' + data + '" href="#"><i class="' + icon + '"></i></a>');
// }

$(document).ready(function() {
    function showTickers() {
        $(CONTENT_TICKERS).html("");

        $.getJSON(ENDPOINT_URL + "/data/tickers/list", (response) => {
            if(response["status"] == "ok") {
                const tickers = response["message"];
            
                for(ticker of tickers) {
                    var newBox = $('<div class="box"></div>');
                    newBox.text(ticker["coin"] + " - " + ticker["currency"]);

                    const deleteButton = $('<a class="button dark-blue red-bg btn-ticker-remove" data-coin="' + ticker["coin"] + '" data-currency="' + ticker["currency"] + '" href="#"><i class="fas fa-trash"></i></a>');

                    newBox.append(deleteButton);

                    $(CONTENT_TICKERS).append(newBox);
                }

                var addNewBox = $('<div class="box non-sortable"></div>');
                // addNewBox.html('<select class="dropdown dark-blue-bg"><option value="volvo">Volvo</option><option value="audi">Audi</option></select>');
                const addNewButton = $('<a class="button dark-blue green-bg btn-ticker-add" href="#"><i class="fas fa-plus"></i></a>');

                addNewBox.append(addNewButton);

                $(CONTENT_TICKERS).append(addNewBox);

                $(HEADER_TITLE_RIGHT).html('You have ' + tickers.length + " ticker(s)");
            }
        });
    }

    $(document).on("click", BTN_TICKER_REMOVE, function() {
        const coin = $(this).attr("data-coin");
        const currency = $(this).attr("data-currency");

        $.post(ENDPOINT_URL + "/data/tickers/remove", {coin: coin, currency: currency}, (response) => {
            showTickers();
        });
    });

    $(document).on("click", BTN_TICKER_ADD, function() {
        const coin = prompt("Please enter the name of the coin (eg: Bitcoin)", "");
        if (coin == null || coin == "") {
            alert("Invalid coin name");
            return;
        }

        const currency = prompt("Please enter the name of the currency (eg: USD)", "");
        if (currency == null || currency == "") {
            alert("Invalid currency");
            return;
        }

        $.post(ENDPOINT_URL + "/data/tickers/add", {coin: coin, currency: currency}, (response) => {
            showTickers();
        });
    });

    document.addEventListener('MENU_CHANGED', (event) => {
        if(event.detail.menu == "tickers") {
            $(HEADER_TITLE).html("Tickers");
            $(HEADER_TITLE_RIGHT).html('Getting data <i class="fas fa-circle-notch fa-spin"></i>');
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