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

        void setServer(AsyncWebServer *server);

        void WebServerStart();

    private:
        Manager *manager;

        AsyncWebServer *server;
};

#endif