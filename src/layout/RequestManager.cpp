
#include "RequestManager.h"

#include "Manager.h"

RequestManager::RequestManager(Manager *_manager) {
    manager = _manager;

    // server = new AsyncWebServer(80);

    // WebServerStart();
};

RequestManager::~RequestManager() {
};

void RequestManager::requestNotFound(AsyncWebServerRequest *request) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& response = jsonBuffer.createObject();

    response["status"] = "error";
    response["message"] = "Endpoint not found";
    
    String jsonStr;
    response.printTo(jsonStr);
    request->send(200, "application/json", jsonStr);
};

void RequestManager::requestWifiStatus(AsyncWebServerRequest *request) {
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

void RequestManager::requestWifiList(AsyncWebServerRequest *request) {
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

void RequestManager::requestWifiConnect(AsyncWebServerRequest *request) {
    if(request->params() != 2) {
        return;
    }

    String ssid_name = request->getParam(0)->name();
    String ssid_value = request->getParam(0)->value();

    String password_name = request->getParam(1)->name();
    String password_value = request->getParam(1)->value();

    if(ssid_name.equals("ssid") && password_name.equals("password")) {
        Serial.print("Connect to ");
        Serial.print(ssid_value);
        Serial.print(" with password ");
        Serial.println(password_value);

        manager->settings->set("ssid", ssid_value.c_str());
        manager->settings->set("password", password_value.c_str());

        manager->utils->disconnectWifi();
        manager->utils->connectWifi(ssid_value.c_str(), password_value.c_str());
    }
};

void RequestManager::requestWifiDisconnect(AsyncWebServerRequest *request) {
    manager->utils->disconnectWifi();
};


void RequestManager::setServer(AsyncWebServer *_server) {
    server = server;

}

// void RequestManager::WebServerStart()
// {
//     // if(!connectWifi()) {
//     //     if(!connectAP()) {
//     //         Serial.println("Unable to connect to Wifi or to create Access Point");
//     //         esp_restart();
//     //     }
//     // }

//     if (MDNS.begin("ttgo"))
//     {
//         Serial.println("MDNS responder started");
//     }

//     server->serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");

//     server->on("/display/draw", HTTP_POST, [this](AsyncWebServerRequest *request) {
//         request->send(200, "text/plain", "");

//         if(request->params() == 0) {
//             return;
//         }

//         String name = request->getParam(0)->name();
//         String params = request->getParam(0)->value();

//         if(name.equals("body")) {
//             manager->render->drawFromJson(params);
//         }
//     });

//     server->on("/data/wifi/list", HTTP_GET, [this](AsyncWebServerRequest *request) {
//         manager->requestManager->requestWifiList(request);
//     });

//     server->on("/data/wifi/status", HTTP_GET, [this](AsyncWebServerRequest *request) {
//         manager->requestManager->requestWifiStatus(request);
//     });

//     server->on("/data/wifi/connect", HTTP_POST, [this](AsyncWebServerRequest *request) {
//         manager->requestManager->requestWifiConnect(request);
//     });

//     server->on("/data/wifi/disconnect", HTTP_POST, [this](AsyncWebServerRequest *request) {
//         manager->requestManager->requestWifiDisconnect(request);
//     });

//     server->onNotFound([this](AsyncWebServerRequest *request) {
//         manager->requestManager->requestNotFound(request);
//     });

//     MDNS.addService("http", "tcp", 80);

//     server->begin();
// }