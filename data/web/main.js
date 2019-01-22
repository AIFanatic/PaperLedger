// const ENDPOINT_URL = "";
// const ENDPOINT_URL = "http://192.168.1.1";
const ENDPOINT_URL = "http://192.168.8.108";
// const ENDPOINT_URL = "/mock";
const ENDPOINT_TICKERS = "https://api.coingecko.com/api/v3";

const CONTENT_DASHBOARD = ".main > .content > .dashboard";
const CONTENT_NETWORK = ".main > .content > .network";
const CONTENT_TICKERS = ".main > .content > .tickers";
const CONTENT_ALARMS = ".main > .content > .alarms";
const CONTENT_SETUP = ".main > .content > .setup";

// TODO: Clean
const SUBCONTENT_DASHBOARD = CONTENT_DASHBOARD + " > .content .sub-content";
const SUBCONTENT_TICKERS = CONTENT_TICKERS + " > .sub-content";
const SUBCONTENT_ALARMS = CONTENT_ALARMS + " > .sub-content";
const SUBCONTENT_SETUP = CONTENT_SETUP + " > .sub-content";

const MAIN = ".main";

const NAV = ".nav";
const NAV_BUTTON = ".nav-button";
const NAV_OPEN_BUTTON = ".nav-open-button";

const HEADER_TITLE = ".main > .header > .title";
const HEADER_TITLE_RIGHT = ".main > .header > .right";

const BTN_NETWORK_DISCONNECT = ".btn-network-disconnect";
const BTN_NETWORK_CONNECT = ".btn-network-connect";

const BTN_TICKER_ADD = ".btn-ticker-add";
const BTN_TICKER_REMOVE = ".btn-ticker-remove";
const BTN_ALARMS = ".btn-alarms";
const BTN_ALARMS_ADD = ".btn-alarms-add";
const BTN_ALARMS_REMOVE = ".btn-alarms-remove";
const BTN_ALARMS_TYPE = ".btn-alarms-type";

const BTN_SETTINGS_UPDATE = ".btn-settings-update";

const INPUT_TICKERS_COIN = ".tickers .input-coin";
const INPUT_TICKERS_CURRENCY = ".tickers .input-currency";

const INPUT_ALARMS_COIN = ".alarms .input-coin";
const INPUT_ALARMS_PRICE = ".alarms .input-price";
const INPUT_ALARMS_DURATION = ".alarms .input-duration";

const LIST_TICKERS_COINS = $(INPUT_TICKERS_COIN).immybox({choices: [],showArrow: false});
const LIST_TICKERS_CURRENCIES = $(INPUT_TICKERS_CURRENCY).immybox({choices: [],showArrow: false});

const LIST_ALARMS_COINS = $(INPUT_ALARMS_COIN).immybox({choices: [],showArrow: false});

const INPUT_UPDATE_FILE = CONTENT_SETUP + " .input-update-file";

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

            $(NAV).removeClass("nav-mobile");
            $(MAIN).removeClass("main-filter");
        }
    });

    $(document).on("click", NAV_OPEN_BUTTON, function() {
        $(NAV).toggleClass("nav-mobile");
        $(MAIN).toggleClass("main-filter");
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

                var tickersCount = 0;
                for(ticker of tickers) {
                    var newBox = $('<div class="box"></div>');
                    newBox.text(ticker["coin"] + " - " + ticker["currency"]);
                    newBox.attr("data-index", tickersCount);

                    var deleteButton = $('<a class="button dark-blue red-bg btn-ticker-remove" href="#"><i class="fas fa-trash"></i></a>');

                    newBox.append(deleteButton);

                    $(SUBCONTENT_TICKERS).append(newBox);
                    
                    tickersCount++;
                }

                $(HEADER_TITLE_RIGHT).html('You have ' + tickers.length + " ticker(s)");
            }
        });
    }

    $(document).on("click", BTN_TICKER_REMOVE, function() {
        const parent = $(this).parent(".box");
        const index = parent.attr("data-index");

        $.post(ENDPOINT_URL + "/data/tickers/remove", {index: index}, (response) => {
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
});

/* ALARMS */
$(document).ready(function() {
    function showCoins() {
        $.getJSON(ENDPOINT_URL + "/data/tickers/list", (response) => {
            if(response["status"] == "ok") {
                const tickers = response["message"];

                var tickersCount = 0;
                for(ticker of tickers) {
                    LIST_ALARMS_COINS[0].options.choices.push({text: ticker["coin"] + " - " + ticker["currency"], value: tickersCount});

                    tickersCount++;
                }
            }
        });
    }
    function showAlarms() {
        $(SUBCONTENT_ALARMS).html("");

        $.getJSON(ENDPOINT_URL + "/data/alarms/list", (response) => {
            if(response["status"] == "ok") {
                const alarms = response["message"];
                var alarmCount = 0;
                for(alarm of alarms) {
                    var typeIcon = '<i class="fas fa-caret-up"></i>';
                    if(alarm["type"] == "below") {
                        typeIcon = '<i class="fas fa-caret-down"></i>';
                    }

                    var newBox = $('<div class="box"></div>');
                    newBox.html('Price: ' + typeIcon + " " + alarm["price"] + " - Duration: " + alarm["duration"] + 's');
                    newBox.attr("data-index", alarmCount);

                    var deleteButton = $('<a class="button dark-blue red-bg btn-alarms-remove" href="#"><i class="fas fa-trash"></i></a>');

                    newBox.append(deleteButton);

                    alarmCount++;

                    $(SUBCONTENT_ALARMS).append(newBox);
                }

                $(HEADER_TITLE_RIGHT).html('You have ' + alarms.length + " alarm(s)");
            }
        });
    }

    $(document).on("click", BTN_ALARMS_REMOVE, function() {
        const parent = $(this).parent(".box");
        const index = parent.attr("data-index");

        $.post(ENDPOINT_URL + "/data/alarms/remove", {index: index}, (response) => {
            showAlarms();
        });
    });

    $(document).on("click", BTN_ALARMS_ADD, function() {
        if(LIST_ALARMS_COINS[0].selectedChoice === null || LIST_ALARMS_COINS[0].selectedChoice === null) {
            alert("Please select a coin");
            return;
        }

        const coinIndex = LIST_ALARMS_COINS[0].selectedChoice.value;
        const price = $(INPUT_ALARMS_PRICE).val();
        const duration = $(INPUT_ALARMS_DURATION).val();
        const type = $(this).siblings(BTN_ALARMS_TYPE).attr("data-type");

        if(isNaN(price) || isNaN(duration) || price == 0 || duration == 0) {
            alert("Please enter a valid price and duration");
            return;
        }

        $.post(ENDPOINT_URL + "/data/alarms/add", {coinIndex: coinIndex, price: price, duration: duration, type: type}, (response) => {
            $(INPUT_ALARMS_PRICE).val("");
            $(INPUT_ALARMS_DURATION).val("");

            showAlarms();
        });
    });

    $(document).on("click", BTN_ALARMS_TYPE, function(e) {
        e.preventDefault();
        const type = $(this).attr("data-type");
        if(type == 0) {
            $(this).removeClass("green");
            $(this).addClass("red");
            $(this).html('<i class="fas fa-caret-down"></i>')
            $(this).attr("data-type", "1");
        }
        else if(type == 1) {
            $(this).removeClass("red");
            $(this).addClass("green");
            $(this).html('<i class="fas fa-caret-up"></i>')
            $(this).attr("data-type", "0");
        }
    });

    document.addEventListener('MENU_CHANGED', (event) => {
        if(event.detail.menu == "alarms") {
            $(HEADER_TITLE).html("Alarms");
            $(HEADER_TITLE_RIGHT).html('Getting data <i class="fas fa-circle-notch fa-spin"></i>');

            showCoins();
            showAlarms();
        }
    });

});


/* SETUP */
$(document).ready(function() {
    function showSettings() {
        $(SUBCONTENT_SETUP).html("");

        $.getJSON(ENDPOINT_URL + "/data/settings/list", (response) => {
            if(response["status"] == "ok") {
                const settings = response["message"];

                console.log(settings)

                for (var key in settings) {
                    if (settings.hasOwnProperty(key)) {
                        var settingParsed = key.replace(/_/g, " ");
                        settingParsed = settingParsed.charAt(0).toUpperCase() + settingParsed.slice(1);

                        var newBox = $('<div class="box"></div>');
                        newBox.text(settingParsed + ": " + settings[key]);

                        var button = $('<a class="button dark-blue yellow-bg btn-settings-update" href="#"><i class="fas fa-edit"></i></a>');
                        button.attr("data-name", key);
                        button.attr("data-value", settings[key]);

                        newBox.append(button);

                        $(SUBCONTENT_SETUP).append(newBox);
                    }
                }

                $(HEADER_TITLE_RIGHT).html("");
            }
        });
    }

    $(document).on("click", BTN_SETTINGS_UPDATE, function() {
        const name = $(this).attr("data-name");
        const value = $(this).attr("data-value");

        var newValue = prompt("Please enter the new value", value);

        if(newValue == null || isNaN(newValue) || newValue == 0) {
            alert("Invalid value entered");
            return;
        }

        $.post(ENDPOINT_URL + "/data/settings/change", {name: name, value: newValue}, (response) => {
            showSettings();
        });
    });

    $(document).on("change", INPUT_UPDATE_FILE, function() {
        $(HEADER_TITLE_RIGHT).html('Updating: <span>0</span>% <i class="fas fa-circle-notch fa-spin"></i>');

        var headerPercentage = $(HEADER_TITLE_RIGHT).children("span");

        const file = $(this).get(0).files[0], formData = new FormData();

        formData.append('file', file);

        $.ajax({
            url: ENDPOINT_URL + "/update",
            type: 'POST',
            contentType: false,
            cache: false,
            processData: false,
            data: formData,
            xhr: function () {
                var jqXHR = null;
                if ( window.ActiveXObject ) {
                    jqXHR = new window.ActiveXObject( "Microsoft.XMLHTTP" );
                }
                else {
                    jqXHR = new window.XMLHttpRequest();
                }
                //Upload progress
                jqXHR.upload.addEventListener("progress", function(evt) {
                    if (evt.lengthComputable) {
                        var percentComplete = Math.round((evt.loaded * 100) / evt.total);
                        $(headerPercentage).text(percentComplete);
                    }
                }, false );
                return jqXHR;
            },
            success: function(data) {
                if(data["message"] == 0) {
                    $(HEADER_TITLE_RIGHT).html("Updated successfully");
                    return;
                }
                $(HEADER_TITLE_RIGHT).html("Update failed: " + data["message"]);
            },
            error: function(data) {
                $(HEADER_TITLE_RIGHT).html("Update failed: " + data);
            }
        });
    });

    document.addEventListener('MENU_CHANGED', (event) => {
        if(event.detail.menu == "setup") {
            $(HEADER_TITLE).html("Setup");
            $(HEADER_TITLE_RIGHT).html('Getting data <i class="fas fa-circle-notch fa-spin"></i>');
            showSettings();
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
        if(message["internet"] == false) {
            console.log(message["internet"] == false)
            $(SUBCONTENT_DASHBOARD).slideDown();
            return;
        }

        $( ".nav-button" ).removeClass("disabled");
    }
});