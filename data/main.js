// Constants
const INKTICKER_URL = "http://192.168.8.100";

const NETWORK_TABLE = document.getElementById("network-table");
const NETWORK_TABLE_BODY = NETWORK_TABLE.getElementsByTagName('tbody')[0];

const WIFI_AUTH_ALGO = ["OPEN", "WEP", "WPA_PSK", "WPA2_PSK", "WPA_WPA2_PSK", "WPA2_ENTERPRISE"]

// Vars
var connectedNetwork;

// Helpers
const getJSON = function(url, callback) {
    var xhr = new XMLHttpRequest();
    xhr.open('GET', url, true);
    xhr.responseType = 'json';
    xhr.onload = function() {
    var status = xhr.status;
    if (status === 200) {
        callback(null, xhr.response);
    } else {
        callback(status, xhr.response);
    }
    };
    xhr.send();
};

var currentMenu = "tickers";

function showMenu(menu) {
    if(currentMenu !== menu) {
        document.getElementById("menu-" + currentMenu).style.display = "none";
        document.getElementById("menu-" + menu).style.display = "initial";

        currentMenu = menu;

        return true;
    }

    return false;
}

function showTickers() {
    if(!showMenu("tickers")) {
        return;
    }
}


function getNetworks(currentNetwork) {
    getJSON(INKTICKER_URL + "/data/wifi/list", (status, response) => {
        if(response["status"] == "ok") {
            NETWORK_TABLE_BODY.innerHTML = "";
            const networks = response["message"];

            for(network of networks) {
                var row = NETWORK_TABLE_BODY.insertRow(NETWORK_TABLE.rows.length - 1);
                var ssid_col = row.insertCell(0);
                var rssi_col = row.insertCell(1);
                var algo_col = row.insertCell(2);
                var action_col = row.insertCell(3);

                ssid_col.innerHTML = network["ssid"];
                rssi_col.innerHTML = network["rssi"] + " dBm";
                algo_col.innerHTML = WIFI_AUTH_ALGO[network["algo"]];

                // Means we are connec
                if(network["ssid"] == currentNetwork) {
                    action_col.innerHTML = "<button>Disconnect</button>";
                    continue;
                }

                action_col.innerHTML = "<button>Connect</button>";
            }
        }
    });
}

function showNetwork() {
    if(!showMenu("network")) {
        return;
    }

    getJSON(INKTICKER_URL + "/data/wifi/status", (status, response) => {
        if(response["status"] == "ok") {
            currentNetwork = response["message"]["ssid"];

            getNetworks(currentNetwork);
        }
    });
}