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
    if(request->params() != 7) {
        manager->webserver->requestInvalid(request);
        return;
    }

    String id_name = request->getParam(0)->name();
    String id_value = request->getParam(0)->value();

    String currency_name = request->getParam(1)->name();
    String currency_value = request->getParam(1)->value();

    String price_name = request->getParam(2)->name();
    String price_value = request->getParam(2)->value();

    String duration_name = request->getParam(3)->name();
    String duration_value = request->getParam(3)->value();

    String type_name = request->getParam(4)->name();
    String type_value = request->getParam(4)->value();

    String frequency_name = request->getParam(5)->name();
    String frequency_value = request->getParam(5)->value();

    String beeps_name = request->getParam(6)->name();
    String beeps_value = request->getParam(6)->value();

    if(!id_name.equals("id") || !currency_name.equals("currency") || 
       !price_name.equals("price") || !duration_name.equals("duration") || 
       !type_name.equals("type") || !frequency_name.equals("frequency") || 
       !beeps_name.equals("beeps")) {
        manager->webserver->requestInvalid(request);
        return;
    }

    bool ret = add(
        id_value.c_str(), currency_value.c_str(), 
        price_value.c_str(), duration_value.toInt(), 
        type_value.toInt(), frequency_value.toInt(), 
        beeps_value.toInt()
    );

    request->send(200, "application/json", "{\"status\":\"ok\",\"message\":" + String(ret) + "}");
};

void Alarms::requestRemoveAlarms(AsyncWebServerRequest *request) {
    if(request->params() != 3) {
        manager->webserver->requestInvalid(request);
        return;
    }

    String id_name = request->getParam(0)->name();
    String id_value = request->getParam(0)->value();

    String currency_name = request->getParam(1)->name();
    String currency_value = request->getParam(1)->value();

    String index_name = request->getParam(2)->name();
    String index_value = request->getParam(2)->value();

    if(!id_name.equals("id") || !currency_name.equals("currency") || !index_name.equals("index")) {
        manager->webserver->requestInvalid(request);
        return;
    }

    bool ret = remove(id_value.c_str(), currency_value.c_str(), index_value.toInt());

    request->send(200, "application/json", "{\"status\":\"ok\",\"message\":" + String(ret) + "}");
};