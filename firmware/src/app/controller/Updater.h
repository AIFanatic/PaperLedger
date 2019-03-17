#ifndef Updater_h
#define Updater_h

#include <Arduino.h>
#include <ESPAsyncWebserver.h>
#include <ArduinoJson.h>

class Manager;
class UpdateView;

class Updater {
    public:
        Updater(Manager *_manager);
        ~Updater(void);

        void requestUpdate(AsyncWebServerRequest *request);
        void requestUpdateUpload(AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final);

    private:
        Manager *manager;
        UpdateView *updateView;
        
        const char *_err2str(uint8_t _error);
};

#endif