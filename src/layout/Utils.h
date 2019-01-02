#ifndef Utils_h
#define Utils_h

#include <WiFi.h>

#define WIFI_MAX_TRIES 1

class Utils {
    public:
        Utils();
        ~Utils(void);

        bool disconnectWifi();
        bool reconnectWifi();
        bool connectAP(const char *apName);
        bool connectWifi(const char *ssid, const char *password);
        String getWifiIP();

    private:
        IPAddress apIP = IPAddress(192, 168, 1, 1);

};

#endif