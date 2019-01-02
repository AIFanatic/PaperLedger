#include "settings.h"

#include "./layout/Manager.h"
// #include "./RequestManager.h"

// #include "./layout/helpers/LayoutList.h"

#include <WiFi.h>
// #include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESPmDNS.h>

#include "esp_wifi.h"
#include "Esp.h"

Manager *manager;

AsyncWebServer server(80);

void WebServerStart(void)
{
    // if(!connectWifi()) {
    //     if(!connectAP()) {
    //         Serial.println("Unable to connect to Wifi or to create Access Point");
    //         esp_restart();
    //     }
    // }

    if (MDNS.begin("ttgo"))
    {
        Serial.println("MDNS responder started");
    }

    server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");

    server.on("/display/draw", HTTP_POST, [](AsyncWebServerRequest *request) {
        request->send(200, "text/plain", "");

        if(request->params() == 0) {
            return;
        }

        String name = request->getParam(0)->name();
        String params = request->getParam(0)->value();

        if(name.equals("body")) {
            manager->render->drawFromJson(params);
        }
    });

    server.on("/data/wifi/list", HTTP_GET, [](AsyncWebServerRequest *request) {
        manager->requestManager->requestWifiList(request);
    });

    server.on("/data/wifi/status", HTTP_GET, [](AsyncWebServerRequest *request) {
        manager->requestManager->requestWifiStatus(request);
    });

    server.on("/data/wifi/connect", HTTP_POST, [](AsyncWebServerRequest *request) {
        manager->requestManager->requestWifiConnect(request);
    });

    server.on("/data/wifi/disconnect", HTTP_POST, [](AsyncWebServerRequest *request) {
        manager->requestManager->requestWifiDisconnect(request);
    });

    server.onNotFound([](AsyncWebServerRequest *request) {
        manager->requestManager->requestNotFound(request);
    });

    MDNS.addService("http", "tcp", 80);

    server.begin();
}

void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);

    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
   
    // Render *render = new Render();

    manager = new Manager();
    manager->show(0);

    WebServerStart();
    // manager->requestManager->setServer(&server);

    // LayoutList *list = new LayoutList(render);
    // list->init(128, 32, 160, 80, 18, BLACK);
    // list->add("Status");
    // list->add("Connect");
    // list->add("Disconnect");
    // list->add("Back");
    // list->draw();

    // delay(5000);
    // list->setActive(list->getActive()+1);
    // delay(5000);
    // list->setActive(list->getActive()+1);

    // File file;
    // manager->filesystem->readFile(SD, "/wallet.json", file);

    // while(file.available()){
    //     Serial.write(file.read());
    // }

    // file.close();
}

void loop() {
    manager->update();
}