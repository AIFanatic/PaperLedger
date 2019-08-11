#ifndef Networking_h
#define Networking_h

#include <HTTPClient.h>
#include <ESPAsyncWebServer.h>
#include <ESPmDNS.h>
#include <ArduinoJson.h>

#include <Update.h>

class Manager;

class WebServer {
    public:
        WebServer(Manager *_manager);
        ~WebServer(void);

        void update();

        String get(String url);
        String post(String url, String params);

        void requestWifiStatus(AsyncWebServerRequest *request);
        void requestWifiList(AsyncWebServerRequest *request);
        void requestWifiConnect(AsyncWebServerRequest *request);
        void requestWifiDisconnect(AsyncWebServerRequest *request);

        void requestNotFound(AsyncWebServerRequest *request);
        void requestInvalid(AsyncWebServerRequest *request);

        bool disconnectWifi();
        bool reconnectWifi();
        bool connectAP(const char *apName);
        bool connectWifi(const char *ssid, const char *password);
        String getWifiIP();
        String getWifiSSID();
        int getWifiSignal();
        wifi_mode_t getWifiMode();

        bool needNetworkReconnect = false;
        bool hasInternetAccess = false;

    private:
        void connectNetwork();
        void connectInternet();

        void begin();
        void reset();

        Manager *manager;

        IPAddress apIP = IPAddress(192, 168, 4, 1);
        AsyncWebServer server = AsyncWebServer(80);
        HTTPClient http; 
};

#endif