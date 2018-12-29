#include "settings.h"

#include "Render.h"
#include "Layout.h"
#include "LayoutList.h"

#include <WiFi.h>
// #include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESPmDNS.h>

#include "esp_wifi.h"
#include "Esp.h"

Render *render;
Layout *layout;

AsyncWebServer server(80);

void WebServerStart(void)
{

    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    while (WiFi.waitForConnectResult() != WL_CONNECTED)
    {
        Serial.print(".");
        esp_restart();
    }
    Serial.println(F("WiFi connected"));
    Serial.println("");
    Serial.println(WiFi.localIP());

    if (MDNS.begin("ttgo"))
    {
        Serial.println("MDNS responder started");
    }

    server.on("/display/draw", HTTP_POST, [](AsyncWebServerRequest *request) {
        request->send(200, "text/plain", "");

        if(request->params() == 0) {
            return;
        }

        String name = request->getParam(0)->name();
        String params = request->getParam(0)->value();

        if(name.equals("body")) {
            render->drawFromJson(params);
        }
    });

    server.on("/display/clear", HTTP_POST, [](AsyncWebServerRequest *request) {
        request->send(200, "text/plain", "");

        render->clearScreen();
    });

    server.on("/display/clearBuffer", HTTP_POST, [](AsyncWebServerRequest *request) {
        request->send(200, "text/plain", "");

        render->clearBuffer();
    });

    server.onNotFound([](AsyncWebServerRequest *request) {
        request->send(404, "text/plain", "Not found");
    });

    MDNS.addService("http", "tcp", 80);

    server.begin();
}

void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);
   
    render = new Render();
    // LayoutList *list = new LayoutList(render);
    // list->init(10, 10, 128, 64, 12);
    // list->add("Hello");
    // list->add("World");
    // list->add("Hey");
    // // list->add("you");
    // list->draw();

    // delay(5000);
    // list->setActive(list->getActive()+1);
    // delay(5000);
    // list->setActive(list->getActive()+1);


    layout = new Layout(render);

    WebServerStart();
}

void loop() {
    layout->update();
}