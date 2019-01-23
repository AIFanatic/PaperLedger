#include "Alarms.h"

#include "Manager.h"

Alarms::Alarms(Manager *_manager) {
    manager = _manager;

    bool tickersFileExists = manager->filesystem->exists(SPIFFS, FILE_TICKERS);

    if(!tickersFileExists) {
        Serial.print("Tickers.json is not valid, creating...");

        manager->filesystem->writeFile(SPIFFS, FILE_TICKERS, "[]");
    }
};

Alarms::~Alarms() {
};

bool Alarms::add(const char *id, const char *currency, const char *price, int duration, int type) {

    int coinIndex = manager->tickers->getIndexOf(id, currency);

    if(coinIndex == -1) {
        return false;
    }

    File tickersFile;
    DynamicJsonBuffer jsonBuffer;

    manager->filesystem->readFile(SPIFFS, FILE_TICKERS, tickersFile);
    JsonArray& tickersArray = jsonBuffer.parse(tickersFile);

    tickersFile.close();

    DynamicJsonBuffer alarmBuffer;
    JsonObject& alarm = alarmBuffer.createObject();
    alarm["price"] = price;
    alarm["duration"] = duration;
    alarm["type"] = type;

    tickersArray[coinIndex]["alarms"].as<JsonArray>().add(alarm);
    
    String str;
    tickersArray.printTo(str);
    return manager->filesystem->writeFile(SPIFFS, FILE_TICKERS, str.c_str());
}

bool Alarms::remove(const char *id, const char *currency, int index) {
    int coinIndex = manager->tickers->getIndexOf(id, currency);

    if(coinIndex == -1) {
        return false;
    }

    File tickersFile;
    DynamicJsonBuffer jsonBuffer;

    manager->filesystem->readFile(SPIFFS, FILE_TICKERS, tickersFile);
    JsonArray& tickersArray = jsonBuffer.parse(tickersFile);

    tickersFile.close();

    tickersArray[coinIndex]["alarms"].as<JsonArray>().remove(index);

    String str;
    tickersArray.printTo(str);

    return manager->filesystem->writeFile(SPIFFS, FILE_TICKERS, str.c_str());
}

void Alarms::checkAlarms() {
    JsonArray& tickersArray = manager->tickers->get();

    bool alarmTriggered = false;

    for(int i = 0; i < tickersArray.size(); i++) {
        double tickerPrice = tickersArray[i]["price"];

        JsonArray& alarms = tickersArray[i]["alarms"].as<JsonArray>();

        for(int j = 0; j < alarms.size(); j++) {
            JsonObject& alarm = alarms[j].as<JsonObject>();

            double price = alarm["price"];
            int duration = alarm["duration"];
            int type = alarm["type"];

            if(tickerPrice > 0) {
                if((type == TYPE_ABOVE && tickerPrice >= price) ||
                   (type == TYPE_BELOW && tickerPrice <= price)) {
                    manager->speaker->tone(2240);
                    delay(duration * 1000);
                    manager->speaker->mute();
                    alarms.remove(j);
                    alarmTriggered = true;
                }
            }
        }
    }

    if(alarmTriggered) {
        String str;
        tickersArray.printTo(str);

        manager->filesystem->writeFile(SPIFFS, FILE_TICKERS, str.c_str());
    }
}