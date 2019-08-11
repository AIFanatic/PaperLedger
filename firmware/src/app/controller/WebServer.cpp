
#include "WebServer.h"

#include "../Manager.h"

WebServer::WebServer(Manager *_manager) {
    manager = _manager;

    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
};

WebServer::~WebServer() {
};

void WebServer::requestNotFound(AsyncWebServerRequest *request) {
    request->send(200, "application/json", "{\"status\":\"error\",\"message\":\"Endpoint not found\"}");
};

void WebServer::requestInvalid(AsyncWebServerRequest *request) {
    request->send(200, "application/json", "{\"status\":\"error\",\"message\":\"Invalid request\"}");
};

void WebServer::requestWifiStatus(AsyncWebServerRequest *request) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& response = jsonBuffer.createObject();
    JsonObject& message = response.createNestedObject("message");

    response["status"] = "ok";

    message["ssid"] = WiFi.SSID();
    message["rssi"] = WiFi.RSSI();
    message["internet"] = hasInternetAccess;
    
    String jsonStr;
    response.printTo(jsonStr);
    request->send(200, "application/json", jsonStr);
};

void WebServer::requestWifiList(AsyncWebServerRequest *request) {
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

void WebServer::requestWifiConnect(AsyncWebServerRequest *request) {
    if(!request->hasParam("ssid", true) || !request->hasParam("password", true)) {
        requestInvalid(request);
        return;
    }

    const char *ssid = request->getParam("ssid", true)->value().c_str();
    const char *password = request->getParam("password", true)->value().c_str();

    manager->settings->set("ssid", ssid);
    manager->settings->set("password", password);

    request->send(200, "application/json", "{\"status\":\"ok\",\"message\":\"connecting\"}");

    needNetworkReconnect = true;
};

void WebServer::requestWifiDisconnect(AsyncWebServerRequest *request) {
    request->send(200, "application/json", "{\"status\":\"ok\",\"message\":\"disconnecting\"}");
    disconnectWifi();
};

void WebServer::reset() {
    server.reset();
}

void WebServer::begin() {
    if (MDNS.begin(AP_NAME))
    {
        Serial.println("MDNS responder started");
    }

    server.serveStatic("/", SPIFFS, "/web").setDefaultFile("index.html");

    server.on("/display/draw", HTTP_POST, [this](AsyncWebServerRequest *request) {
        if(request->params() == 0) {
            requestInvalid(request);
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
        manager->tickers->requestTickers(request);
    });

    server.on("/data/tickers/add", HTTP_POST, [this](AsyncWebServerRequest *request) {
        manager->tickers->requestAddTickers(request);
    });
    
    server.on("/data/tickers/order", HTTP_POST, [this](AsyncWebServerRequest *request) {
        manager->tickers->requestOrderTickers(request);
    });

    server.on("/data/tickers/remove", HTTP_POST, [this](AsyncWebServerRequest *request) {
        manager->tickers->requestRemoveTickers(request);
    });

    server.on("/data/alarms/add", HTTP_POST, [this](AsyncWebServerRequest *request) {
        manager->alarms->requestAddAlarms(request);
    });

    server.on("/data/alarms/remove", HTTP_POST, [this](AsyncWebServerRequest *request) {
        manager->alarms->requestRemoveAlarms(request);
    });

    server.on("/data/settings/list", HTTP_GET, [this](AsyncWebServerRequest *request) {
        manager->settings->requestSettings(request);
    });

    server.on("/data/settings/change", HTTP_POST, [this](AsyncWebServerRequest *request) {
        manager->settings->requestChangeSettings(request);
    });

    server.on("/data/battery/status", HTTP_GET, [this](AsyncWebServerRequest *request) {
        manager->battery->requestBatteryStatus(request);
    });

    server.on("/update", HTTP_POST, [this](AsyncWebServerRequest *request){
        manager->updater->requestUpdate(request);
    },[this](AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final){
        manager->updater->requestUpdateUpload(request, filename, index, data, len, final);
    });

    server.onNotFound([this](AsyncWebServerRequest *request) {
        requestNotFound(request);
    });

    MDNS.addService("http", "tcp", 80);

    server.begin();
}

String WebServer::get(String url) {
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

String WebServer::post(String url, String params) {
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

bool WebServer::disconnectWifi() {
    return WiFi.disconnect();
}

bool WebServer::reconnectWifi() {
    return WiFi.reconnect();
}

bool WebServer::connectAP(const char *apName) {
    WiFi.mode(WIFI_AP);

    if (!WiFi.softAP(apName))
    {
        return false;
    }

    // WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));

    Serial.println(F("AP connected"));
    Serial.println("");
    Serial.println(WiFi.softAPIP());

    return true;
}

bool WebServer::connectWifi(const char *ssid, const char *password) {
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

String WebServer::getWifiIP() {
    if(getWifiMode() == WIFI_MODE_AP) {
        return WiFi.softAPIP().toString();
    }

    return WiFi.localIP().toString();
}

String WebServer::getWifiSSID() {
    return WiFi.SSID();
}

int WebServer::getWifiSignal() {
    return WiFi.RSSI();
}

wifi_mode_t WebServer::getWifiMode() {
    return WiFi.getMode();
}


void WebServer::connectInternet() {
    String response = get(URL_IM_ALIVE);

    if(response.length() == 0) {
        hasInternetAccess = false;
        return;
    }

    hasInternetAccess = true;

    DynamicJsonBuffer jsonBuffer;
    JsonObject& responseJson = jsonBuffer.parse(response);

    int utcOffset = responseJson["utc_offset"];
    String utcOffsetStr = String(utcOffset / 100 * 3600);

    manager->settings->set("utc_offset", utcOffsetStr.c_str());

    Serial.printf("offfset: %s\n", utcOffsetStr.c_str());
}

void WebServer::connectNetwork() {
    String ssid = manager->settings->get("ssid");
    String password = manager->settings->get("password");
    
    if(!connectWifi(ssid.c_str(), password.c_str())) {
        Serial.println("Unable to connect to wifi, creating AP");
        if(!connectAP(AP_NAME)) {
            Serial.println("Unable to connect to Wifi or to create Access Point");
            esp_restart();
        }
    }
}

void WebServer::update() {
    // Its better to handle network reconnects in a loop instead of a request
    if(needNetworkReconnect) {
        hasInternetAccess = false;

        reset();
        disconnectWifi();
        connectNetwork();
        connectInternet();
        begin();

        needNetworkReconnect = false;
    }
}