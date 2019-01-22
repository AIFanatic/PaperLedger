#ifndef Alarms_h
#define Alarms_h

#include <Arduino.h>

#include <ArduinoJson.h>

#include "../Util.h"

class Manager;

class Alarms {
    public:
        Alarms(Manager *_manager);
        ~Alarms(void);

        JsonArray& get();
        bool add(int coinIndex, const char *price, const char *duration, int type);
        bool remove(int index);

        void checkAlarms();

        void reset();

    private:
        Manager *manager;
        
};

#endif