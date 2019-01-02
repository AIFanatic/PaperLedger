// Constants
// const INKTICKER_URL = "http://192.168.8.100";
const INKTICKER_URL = "http://localhost:5500/mock";

const NETWORK_TABLE = "#network-table";

const WIFI_AUTH_ALGO = ["OPEN", "WEP", "WPA_PSK", "WPA2_PSK", "WPA_WPA2_PSK", "WPA2_ENTERPRISE"];

const BTN_MENU_INTRO = "#btn-menu-intro";
const BTN_MENU_TICKERS = "#btn-menu-tickers";
const BTN_MENU_NETWORK = "#btn-menu-network";

const BTN_NETWORK_CONNECT = ".btn-network-connect";
const BTN_NETWORK_DISCONNECT = ".btn-network-disconnect";

// Vars
var currentMenu = "intro";

function showMenu(menu) {
    if(currentMenu !== menu) {
        document.getElementById("menu-" + currentMenu).style.display = "none";
        document.getElementById("menu-" + menu).style.display = "initial";

        currentMenu = menu;

        return true;
    }

    return false;
}

// NETWORK
$(document).ready(function() {

    function getWifiNetworks() {
        $.getJSON(INKTICKER_URL + "/data/wifi/status", (response) => {
            if(response["status"] == "ok") {
                currentNetwork = response["message"]["ssid"];
    
                $.getJSON(INKTICKER_URL + "/data/wifi/list", (response) => {
                    if(response["status"] == "ok") {
                        $(NETWORK_TABLE + " > tbody").html("");
            
                        const networks = response["message"];
            
                        for(network of networks) {
                            var row = $("<tr></tr>");
            
                            row.append("<td> " + network["ssid"] + " </td>");
                            row.append("<td> " + network["rssi"] + " </td>");
                            row.append("<td> " + WIFI_AUTH_ALGO[network["algo"]] + " </td>");
            
                            var action_col = "<td><button data-ssid='"+network["ssid"]+"' class='btn-network-connect')>Connect</button><td>";
                            if(network["ssid"] == currentNetwork) {
                                action_col = "<td><button data-ssid='"+network["ssid"]+"' class='btn-network-disconnect'>Disconnect</button><td>";
                            }
            
                            row.append(action_col);
            
                            $(NETWORK_TABLE + " > tbody").append(row);
                        }
                    }
                });
            }
        });
    }

    $(document).on("click", BTN_NETWORK_CONNECT, function() {
        const ssid = $(this).attr("data-ssid");
        console.log(ssid);

        const password = prompt("Please enter the password for " + ssid + ":", "");
        if (password == null || password == "") {
            alert("Invalid password entered, request cancelled");
            return;
        }

        console.log(password);

        $.post(INKTICKER_URL + "/data/wifi/connect", {ssid: ssid, password: password}, (response) => {
            // getWifiNetworks();
        });
    });

    $(document).on("click", BTN_NETWORK_DISCONNECT, function() {
        const ssid = $(this).attr("data-ssid");
        console.log(ssid);

        $.post(INKTICKER_URL + "/data/wifi/disconnect", (response) => {
            getWifiNetworks();
        });
    });

    // MENUS
    $(document).on("click", BTN_MENU_INTRO, function() {
        showMenu("intro");
    });

    $(document).on("click", BTN_MENU_TICKERS, function() {
        showMenu("tickers");
    });

    $(document).on("click", BTN_MENU_NETWORK, function() {
        if(!showMenu("network")) {
            return;
        }

        getWifiNetworks();
    });
});

// TICKERS
$(document).ready(function() {
    console.log("ready")
});