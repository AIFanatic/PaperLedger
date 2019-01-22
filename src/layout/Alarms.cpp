#include "Alarms.h"

#include "Manager.h"

Alarms::Alarms(Manager *_manager) {
    manager = _manager;

    bool fileExists = manager->filesystem->exists(SPIFFS, FILE_ALARMS);

    if(!fileExists) {
        Serial.print("Alarms.json is not valid, creating...");

        manager->filesystem->writeFile(SPIFFS, FILE_ALARMS, "[]");
    }
};

Alarms::~Alarms() {
};

JsonArray& Alarms::get() {
    File tickersFile;
    manager->filesystem->readFile(SPIFFS, FILE_ALARMS, tickersFile);

    DynamicJsonBuffer jsonBuffer;
    JsonArray& tickersArray = jsonBuffer.parse(tickersFile);
    tickersFile.close();

    return tickersArray;
}

bool Alarms::add(int coinIndex, const char *price, const char *duration, int type) {
    File tickersFile;
    DynamicJsonBuffer jsonBuffer;

    manager->filesystem->readFile(SPIFFS, FILE_ALARMS, tickersFile);
    JsonArray& tickersArray = jsonBuffer.parse(tickersFile);

    tickersFile.close();

    DynamicJsonBuffer objBuffer;
    JsonObject& obj = objBuffer.createObject();
    obj["coinIndex"] = coinIndex;
    obj["price"] = price;
    obj["duration"] = duration;
    obj["type"] = type;

    tickersArray.add(obj);

    String str;
    tickersArray.printTo(str);
    
    return manager->filesystem->writeFile(SPIFFS, FILE_ALARMS, str.c_str());
}

bool Alarms::remove(int index) {
    File tickersFile;
    DynamicJsonBuffer jsonBuffer;

    manager->filesystem->readFile(SPIFFS, FILE_ALARMS, tickersFile);
    JsonArray& tickersArray = jsonBuffer.parse(tickersFile);

    tickersFile.close();

    tickersArray.remove(index);

    String str;
    tickersArray.printTo(str);

    return manager->filesystem->writeFile(SPIFFS, FILE_ALARMS, str.c_str());
}

void Alarms::reset() {
    manager->filesystem->deleteFile(SPIFFS, FILE_ALARMS);
    manager->filesystem->writeFile(SPIFFS, FILE_ALARMS, "[]");
}

void Alarms::checkAlarms() {
}