#include "Alarms.h"

#include "../Manager.h"

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

bool Alarms::add(const char *id, const char *currency, const char *price, int duration, int type, int frequency, int beeps) {

    int coinIndex = manager->tickers->getIndexOf(id, currency);

    if(coinIndex == -1) {
        return false;
    }

    String tickers = manager->tickers->get();
    DynamicJsonBuffer jsonBuffer;
    JsonArray& tickersArray = jsonBuffer.parse(tickers);

    DynamicJsonBuffer alarmBuffer;
    JsonObject& alarm = alarmBuffer.createObject();
    alarm["price"] = price;
    alarm["duration"] = duration;
    alarm["type"] = type;
    alarm["frequency"] = frequency;
    alarm["beeps"] = beeps;

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

    String tickers = manager->tickers->get();
    DynamicJsonBuffer jsonBuffer;
    JsonArray& tickersArray = jsonBuffer.parse(tickers);

    tickersArray[coinIndex]["alarms"].as<JsonArray>().remove(index);

    String str;
    tickersArray.printTo(str);

    return manager->filesystem->writeFile(SPIFFS, FILE_TICKERS, str.c_str());
}

void Alarms::checkAlarms() {
    // JsonArray& tickersArray = manager->tickers->get();

    String str = manager->tickers->get();

    DynamicJsonBuffer buffer;
    JsonArray& tickersArray = buffer.parse(str);

    bool alarmTriggered = false;

    for(int i = 0; i < tickersArray.size(); i++) {
        double tickerPrice = tickersArray[i]["price"];

        JsonArray& alarms = tickersArray[i]["alarms"].as<JsonArray>();

        for(int j = 0; j < alarms.size(); j++) {
            JsonObject& alarm = alarms[j].as<JsonObject>();

            double price = alarm["price"];
            int duration = alarm["duration"];
            int type = alarm["type"];
            int frequency = alarm["frequency"];
            int beeps = alarm["beeps"];

            if(tickerPrice > 0) {
                if((type == TYPE_ABOVE && tickerPrice >= price) ||
                   (type == TYPE_BELOW && tickerPrice <= price)) {
                    // manager->speaker->tone(2240);
                    // delay(duration * 1000);
                    // manager->speaker->mute();
                    manager->speaker->beep(frequency, (duration * 1000) / beeps, beeps);
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

void Alarms::requestAddAlarms(AsyncWebServerRequest *request) {
    if(!request->hasParam("id", true) || !request->hasParam("currency", true) || 
       !request->hasParam("price", true) || !request->hasParam("duration", true) ||
       !request->hasParam("type", true) || !request->hasParam("frequency", true) ||
       !request->hasParam("beeps", true)) {
        manager->webserver->requestInvalid(request);
        return;
    }

    const char *id = request->getParam("id", true)->value().c_str();
    const char *currency = request->getParam("currency", true)->value().c_str();
    const char *price = request->getParam("price", true)->value().c_str();
    int duration = request->getParam("duration", true)->value().toInt();
    int type = request->getParam("type", true)->value().toInt();
    int frequency = request->getParam("frequency", true)->value().toInt();
    int beeps = request->getParam("beeps", true)->value().toInt();


    bool ret = add(
        id, currency, 
        price, duration, 
        type, frequency, 
        beeps
    );

    request->send(200, "application/json", "{\"status\":\"ok\",\"message\":" + String(ret) + "}");
};

void Alarms::requestRemoveAlarms(AsyncWebServerRequest *request) {
    if(!request->hasParam("id", true) || !request->hasParam("currency", true) || !request->hasParam("index", true)) {
        manager->webserver->requestInvalid(request);
        return;
    }

    const char *id = request->getParam("id", true)->value().c_str();
    const char *currency = request->getParam("currency", true)->value().c_str();
    int index = request->getParam("index", true)->value().toInt();

    bool ret = remove(id, currency, index);

    request->send(200, "application/json", "{\"status\":\"ok\",\"message\":" + String(ret) + "}");
};