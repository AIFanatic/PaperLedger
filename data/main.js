// const ENDPOINT_URL = "";
// const ENDPOINT_URL = "http://192.168.1.1";
const ENDPOINT_URL = "http://192.168.8.100";

const CONTENT_NETWORK = ".main > .content > .network";

const NAV_BUTTON = ".nav-button";
const HEADER_TITLE = ".main > .header > .title";
const HEADER_TITLE_RIGHT = ".main > .header > .right";

const BTN_NETWORK_DISCONNECT = ".btn-network-disconnect";
const BTN_NETWORK_CONNECT = ".btn-network-connect";

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

        console.log(menu)

        showMenu(menu);
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
                            console.log(network);

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

        console.log(password);

        $.post(ENDPOINT_URL + "/data/wifi/connect", {ssid: ssid, password: password}, (response) => {
            // showWifiNetworks();
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