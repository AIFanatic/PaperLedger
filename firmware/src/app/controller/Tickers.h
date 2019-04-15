#ifndef Tickers_h
#define Tickers_h

#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

#include "../helpers/Utils.h"

class Manager;

class Tickers {
    public:
        Tickers(Manager *_manager);
        ~Tickers(void);

        String get();

        bool add(const char *id, const char *coin, const char *currency);
        bool remove(const char *id, const char *currency);
        bool remove(int index);
        int getIndexOf(const char *id, const char *currency);
        bool changeOrder(int from, int to);

        bool updateTickers();

        void reset();

        void requestTickers(AsyncWebServerRequest *request);
        void requestAddTickers(AsyncWebServerRequest *request);
        void requestOrderTickers(AsyncWebServerRequest *request);
        void requestRemoveTickers(AsyncWebServerRequest *request);

    private:
        Manager *manager;
};

#endif