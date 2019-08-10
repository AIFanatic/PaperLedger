#ifndef Battery_H_
#define Battery_H_

#include "Arduino.h"
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

class Manager;

class Battery {
public:
    Battery(Manager *_manager);
    ~Battery(void);

    void update();

    void requestBatteryStatus(AsyncWebServerRequest *request);

    bool isCharging = false;
    int chargePercentage = 0;

private:
    bool getIsCharging();
    int getChargePercentage();

    Manager *manager;

    long lastUpdate = 0;
};

#endif