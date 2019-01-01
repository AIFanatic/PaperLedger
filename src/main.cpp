#include "settings.h"

// #include "./layout/Render.h"
#include "./layout/Display.h"
#include "./layout/helpers/LayoutList.h"

#include <WiFi.h>
// #include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESPmDNS.h>

#include "esp_wifi.h"
#include "Esp.h"

Display *display;

AsyncWebServer server(80);

bool connectWifi() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

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

IPAddress apIP = IPAddress(192, 168, 1, 1);
bool connectAP() {
    uint8_t mac[6];
    char apName[18] = {0};

    WiFi.mode(WIFI_AP);

    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));

    sprintf(apName, "inkTicker-%02X:%02X", mac[4], mac[5]);

    if (!WiFi.softAP(apName, NULL, 1, 0, 1))
    {
        Serial.println("AP Config failed.");
        return false;
    }
    Serial.println("AP Config Success.");
    Serial.print("AP MAC: ");
    Serial.println(WiFi.softAPmacAddress());

    return true;
}

void sendAvailableWifi(AsyncWebServerRequest *request) {
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
}

void sendWifiStatus(AsyncWebServerRequest *request) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& response = jsonBuffer.createObject();
    JsonObject& message = response.createNestedObject("message");

    response["status"] = "ok";

    message["ssid"] = WiFi.SSID();
    message["rssi"] = WiFi.RSSI();
    
    String jsonStr;
    response.printTo(jsonStr);
    request->send(200, "application/json", jsonStr);
}

void WebServerStart(void)
{
    if(!connectWifi()) {
        if(!connectAP()) {
            Serial.println("Unable to connect to Wifi or to create Access Point");
            esp_restart();
        }
    }

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
            display->render->drawFromJson(params);
        }
    });

    server.on("/data/wifi/list", HTTP_GET, [](AsyncWebServerRequest *request) {
        sendAvailableWifi(request);
    });

    server.on("/data/wifi/status", HTTP_GET, [](AsyncWebServerRequest *request) {
        sendWifiStatus(request);
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
   
    // Render *render = new Render();

    display = new Display();
    display->show(0);

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

    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");

    WebServerStart();

    // initFilesystem();
}

void loop() {
    display->update();
}