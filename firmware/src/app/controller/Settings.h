#ifndef Settings_h
#define Settings_h

#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

class Manager;

class Settings {
    public:
        Settings(Manager *_manager);
        ~Settings(void);

        String get(const char *name);
        String get();
        bool set(const char *name, const char *value);

        void reset();

        void requestSettings(AsyncWebServerRequest *request);
        void requestChangeSettings(AsyncWebServerRequest *request);

    private:
        Manager *manager;
        
};

#endif