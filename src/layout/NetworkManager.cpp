
#include "NetworkManager.h"

#include "Manager.h"

NetworkManager::NetworkManager(Manager *_manager) {
    manager = _manager;
};

NetworkManager::~NetworkManager() {
};

void NetworkManager::requestNotFound(AsyncWebServerRequest *request) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& response = jsonBuffer.createObject();

    response["status"] = "error";
    response["message"] = "Endpoint not found";
    
    String jsonStr;
    response.printTo(jsonStr);
    request->send(200, "application/json", jsonStr);
};

void NetworkManager::requestWifiStatus(AsyncWebServerRequest *request) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& response = jsonBuffer.createObject();
    JsonObject& message = response.createNestedObject("message");

    response["status"] = "ok";

    message["ssid"] = WiFi.SSID();
    message["rssi"] = WiFi.RSSI();
    
    String jsonStr;
    response.printTo(jsonStr);
    request->send(200, "application/json", jsonStr);
};

void NetworkManager::requestWifiList(AsyncWebServerRequest *request) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& response = jsonBuffer.createObject();

    response["status"] = "ok";

    JsonArray& message = response.createNestedArray("message");

    int n = WiFi.scanNetworks();

    if (n != 0) {
        for (int i = 0; i < n; ++i) {
            JsonObject& newWifi = message.createNestedObject();
            
            newWifi["ssid"] = WiFi.SSID(i);
            newWifi["rssi"] = WiFi.RSSI(i);
            newWifi["algo"] = WiFi.encryptionType(i);
            newWifi.set<int>("algo", WiFi.encryptionType(i));

            delay(10);
        }
    }
    
    String jsonStr;
    response.printTo(jsonStr);
    request->send(200, "application/json", jsonStr);
};

void NetworkManager::requestWifiConnect(AsyncWebServerRequest *request) {
    if(request->params() != 2) {
        request->send(200, "application/json", "{\"status\":\"error\",\"message\":\"Invalid request\"}");
        return;
    }

    String ssid_name = request->getParam(0)->name();
    String ssid_value = request->getParam(0)->value();

    String password_name = request->getParam(1)->name();
    String password_value = request->getParam(1)->value();

    if(!ssid_name.equals("ssid") || !password_name.equals("password")) {
        request->send(200, "application/json", "{\"status\":\"error\",\"message\":\"Invalid request\"}");
        return;
    }

    Serial.print("Connect to ");
    Serial.print(ssid_value);
    Serial.print(" with password ");
    Serial.println(password_value);

    manager->settings->set("ssid", ssid_value.c_str());
    manager->settings->set("password", password_value.c_str());

    request->send(200, "application/json", "{\"status\":\"ok\",\"message\":\"reconnecting\"}");

    needNetworkReconnect = true;
};

void NetworkManager::requestWifiDisconnect(AsyncWebServerRequest *request) {
    disconnectWifi();
};

void NetworkManager::requestTickers(AsyncWebServerRequest *request) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& response = jsonBuffer.createObject();

    response["status"] = "ok";

    response["message"] = manager->tickers->get();

    String str;
    response.printTo(str);
    request->send(200, "application/json", str);
};

void NetworkManager::requestAddTickers(AsyncWebServerRequest *request) {
    if(request->params() != 2) {
        request->send(200, "application/json", "{\"status\":\"error\",\"message\":\"Invalid request\"}");
        return;
    }

    String coin_name = request->getParam(0)->name();
    String coin_value = request->getParam(0)->value();

    String currency_name = request->getParam(1)->name();
    String currency_value = request->getParam(1)->value();

    if(!coin_name.equals("coin") || !currency_name.equals("currency")) {
        request->send(200, "application/json", "{\"status\":\"error\",\"message\":\"Invalid request\"}");
        return;
    }

    int index = manager->tickers->getIndexOf(coin_value.c_str(), currency_value.c_str());

    if(index != -1) {
        request->send(200, "application/json", "{\"status\":\"error\",\"message\":\"Coin already exists\"}");
        return;
    }

    manager->tickers->add(coin_value.c_str(), currency_value.c_str());

    request->send(200, "application/json", "{\"status\":\"ok\",\"message\":\"added\"}");
};

void NetworkManager::requestRemoveTickers(AsyncWebServerRequest *request) {
    if(request->params() != 2) {
        request->send(200, "application/json", "{\"status\":\"error\",\"message\":\"Invalid request\"}");
        return;
    }

    String coin_name = request->getParam(0)->name();
    String coin_value = request->getParam(0)->value();

    String currency_name = request->getParam(1)->name();
    String currency_value = request->getParam(1)->value();

    if(!coin_name.equals("coin") || !currency_name.equals("currency")) {
        request->send(200, "application/json", "{\"status\":\"error\",\"message\":\"Invalid request\"}");
        return;
    }

    manager->tickers->remove(coin_value.c_str(), currency_value.c_str());

    request->send(200, "application/json", "{\"status\":\"ok\",\"message\":\"removed\"}");
};

void NetworkManager::reset() {
    server.reset();
}

void NetworkManager::begin() {
    if (MDNS.begin("ttgo"))
    {
        Serial.println("MDNS responder started");
    }

    server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");

    server.on("/display/draw", HTTP_POST, [this](AsyncWebServerRequest *request) {
        if(request->params() == 0) {
            request->send(200, "application/json", "{\"status\":\"error\",\"message\":\"Invalid request\"}");
            return;
        }

        String name = request->getParam(0)->name();
        String params = request->getParam(0)->value();

        if(name.equals("body")) {
            manager->render->drawFromJson(params);
            request->send(200, "application/json", "{\"status\":\"ok\",\"message\":\"drawing\"}");
        }
    });

    server.on("/data/wifi/list", HTTP_GET, [this](AsyncWebServerRequest *request) {
        requestWifiList(request);
    });

    server.on("/data/wifi/status", HTTP_GET, [this](AsyncWebServerRequest *request) {
        requestWifiStatus(request);
    });

    server.on("/data/wifi/connect", HTTP_POST, [this](AsyncWebServerRequest *request) {
        requestWifiConnect(request);
    });

    server.on("/data/wifi/disconnect", HTTP_POST, [this](AsyncWebServerRequest *request) {
        requestWifiDisconnect(request);
    });

    server.on("/data/tickers/list", HTTP_GET, [this](AsyncWebServerRequest *request) {
        requestTickers(request);
    });

    server.on("/data/tickers/add", HTTP_POST, [this](AsyncWebServerRequest *request) {
        requestAddTickers(request);
    });

    server.on("/data/tickers/remove", HTTP_POST, [this](AsyncWebServerRequest *request) {
        requestRemoveTickers(request);
    });

    server.onNotFound([this](AsyncWebServerRequest *request) {
        requestNotFound(request);
    });

    MDNS.addService("http", "tcp", 80);

    server.begin();
}

String NetworkManager::get(String url) {
    http.begin(url);
    int httpCode = http.GET();
 
    if (httpCode == 0) {
        Serial.println("Error on HTTP request");
        return "";
    }
 
    String payload = http.getString();
    
    http.end(); //Free the resources

    return payload;
};

String NetworkManager::post(String url, String params) {
    http.begin(url);
    int httpCode = http.POST(params);
 
    if (httpCode == 0) {
        Serial.println("Error on HTTP request");
        return "";
    }
 
    String payload = http.getString();
    
    http.end(); //Free the resources

    return payload;
}

bool NetworkManager::disconnectWifi() {
    return WiFi.disconnect();
}

bool NetworkManager::reconnectWifi() {
    return WiFi.reconnect();
}

bool NetworkManager::connectAP(const char *apName) {
    WiFi.mode(WIFI_AP);

    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));

    if (!WiFi.softAP(apName, NULL, 1, 0, 1))
    {
        return false;
    }

    return true;
}

bool NetworkManager::connectWifi(const char *ssid, const char *password) {
    if(!ssid || strlen(ssid) == 0) {
        return false;
    }

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    int MAX_TRIES = 1;
    while (WiFi.waitForConnectResult() != WL_CONNECTED)
    {
        Serial.print(".");

        if(MAX_TRIES == 0) {
            return false;
        }

        MAX_TRIES--;
        delay(1000);
    }
    Serial.println(F("WiFi connected"));
    Serial.println("");
    Serial.println(WiFi.localIP());

    return true;
}

String NetworkManager::getWifiIP() {
    return WiFi.localIP().toString();
}


void NetworkManager::checkInternetAccess() {
    String response = get(URL_IM_ALIVE);

    if(response.length() == 0) {
        return;
    }

    hasInternetAccess = true;
    Serial.println("Im alive!!!");
}

void NetworkManager::connectNetwork() {
    String ssid = manager->settings->get("ssid");
    String password = manager->settings->get("password");

    Serial.println(ssid);
    Serial.println(password);
    
    if(!connectWifi(ssid.c_str(), password.c_str())) {
        Serial.println("Unable to connect to wifi, creating AP");
        if(!connectAP(AP_NAME)) {
            Serial.println("Unable to connect to Wifi or to create Access Point");
            esp_restart();
        }
    }
}

void NetworkManager::update() {
    // Its better to handle network reconnects in a loop instead of a request
    if(needNetworkReconnect) {
        hasInternetAccess = false;

        reset();
        disconnectWifi();
        connectNetwork();
        checkInternetAccess();
        begin();

        needNetworkReconnect = false;
    }
}