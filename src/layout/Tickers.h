#ifndef Tickers_h
#define Tickers_h

#include <Arduino.h>

#include <ArduinoJson.h>

class Manager;

class Tickers {
    public:
        Tickers(Manager *_manager);
        ~Tickers(void);

        JsonArray& get();
        bool add(const char *coin, const char *currency);
        bool remove(const char *coin, const char *currency);
        bool remove(int index);
        int getIndexOf(const char *coin, const char *currency);

        String getTickerData(const char *coins, const char *currencies);

        bool updatePrices();

        void reset();

    private:
        Manager *manager;
        
};

#endif