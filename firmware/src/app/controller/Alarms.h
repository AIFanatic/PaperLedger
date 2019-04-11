#ifndef Alarms_h
#define Alarms_h

#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

#include "../helpers/Utils.h"

class Manager;

class Alarms {
    public:
        Alarms(Manager *_manager);
        ~Alarms(void);

        bool add(const char *id, const char *currency, const char *price, int duration, int type, int frequency, int beeps);
        bool remove(const char *id, const char *currency, int index);

        void checkAlarms();

        void requestAddAlarms(AsyncWebServerRequest *request);
        void requestRemoveAlarms(AsyncWebServerRequest *request);

    private:
        Manager *manager;

        enum TYPES {
            TYPE_ABOVE,
            TYPE_BELOW
        };
        
};

#endif