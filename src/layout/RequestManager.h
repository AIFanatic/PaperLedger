/**
 * TODO
 * 
 * Handling responses properly (instead of a String):
 * https://github.com/me-no-dev/ESPAsyncWebServer#arduinojson-basic-response
 * https://github.com/me-no-dev/ESPAsyncWebServer#arduinojson-advanced-response
 * 
 * OTA Updates:
 * https://github.com/me-no-dev/ESPAsyncWebServer#setting-up-the-server
 * 
 * AsyncWebServer in class:
 * https://github.com/me-no-dev/ESPAsyncWebServer#setup-global-and-class-functions-as-request-handlers
 */

#ifndef RequestManager_h
#define RequestManager_h

#include <ESPAsyncWebServer.h>
#include <ESPmDNS.h>
#include <ArduinoJson.h>

class Manager;

class RequestManager {
    public:
        RequestManager(Manager *_manager);
        ~RequestManager(void);

        void requestWifiStatus(AsyncWebServerRequest *request);
        void requestWifiList(AsyncWebServerRequest *request);
        void requestWifiConnect(AsyncWebServerRequest *request);
        void requestWifiDisconnect(AsyncWebServerRequest *request);
        
        void requestNotFound(AsyncWebServerRequest *request);

        void begin();
        void reset();

    private:
        Manager *manager;

        AsyncWebServer server = AsyncWebServer(80);
};

#endif