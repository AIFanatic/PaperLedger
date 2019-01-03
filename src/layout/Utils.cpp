#include "Utils.h"

Utils::Utils() {

}

Utils::~Utils() {
    
}

bool Utils::disconnectWifi() {
    return WiFi.disconnect();
}

bool Utils::reconnectWifi() {
    return WiFi.reconnect();
}

bool Utils::connectAP(const char *apName) {
    WiFi.mode(WIFI_AP);

    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));

    if (!WiFi.softAP(apName, NULL, 1, 0, 1))
    {
        return false;
    }

    return true;
}

bool Utils::connectWifi(const char *ssid, const char *password) {
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

String Utils::getWifiIP() {
    return WiFi.localIP().toString();
}