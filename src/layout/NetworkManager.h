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

#ifndef NetworkManager_h
#define NetworkManager_h

#include <HTTPClient.h>
#include <ESPAsyncWebServer.h>
#include <ESPmDNS.h>
#include <ArduinoJson.h>

class Manager;

class NetworkManager {
    public:
        NetworkManager(Manager *_manager);
        ~NetworkManager(void);

        void update();

        String get(String url);
        String post(String url, String params);

        void requestWifiStatus(AsyncWebServerRequest *request);
        void requestWifiList(AsyncWebServerRequest *request);
        void requestWifiConnect(AsyncWebServerRequest *request);
        void requestWifiDisconnect(AsyncWebServerRequest *request);
        void requestTickers(AsyncWebServerRequest *request);
        void requestAddTickers(AsyncWebServerRequest *request);
        void requestOrderTickers(AsyncWebServerRequest *request);
        void requestRemoveTickers(AsyncWebServerRequest *request);
        void requestNotFound(AsyncWebServerRequest *request);
        void requestInvalid(AsyncWebServerRequest *request);

        void begin();
        void reset();

        void connectNetwork();
        void checkInternetAccess();

        bool disconnectWifi();
        bool reconnectWifi();
        bool connectAP(const char *apName);
        bool connectWifi(const char *ssid, const char *password);
        String getWifiIP();
        wifi_mode_t getWifiMode();

        bool needNetworkReconnect = false;
        bool hasInternetAccess = false;

    private:
        Manager *manager;

        IPAddress apIP = IPAddress(192, 168, 1, 1);
        AsyncWebServer server = AsyncWebServer(80);
        HTTPClient http;
};

#endif