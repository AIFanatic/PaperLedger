#include "Settings.h"

#include "Manager.h"

Settings::Settings(Manager *_manager) {
    manager = _manager;

    bool settingsExist = manager->filesystem->exists(SPIFFS, FILE_SETTINGS);

    if(!settingsExist) {
        bool wroteSettings = manager->filesystem->writeFile(SPIFFS, FILE_SETTINGS, DEFAULT_SETTINGS);

        if(!wroteSettings) {
            Serial.println("Unable to create settings.json");    
        }
        else {
            Serial.println("Created settings.json");
        }
    }
};

Settings::~Settings() {
};

JsonObject& Settings::get() {
    File settings;
    manager->filesystem->readFile(SPIFFS, FILE_SETTINGS, settings);

    DynamicJsonBuffer jsonBuffer;
    JsonObject& settingsJson = jsonBuffer.parse(settings);
    settings.close();

    // Remove wifi credentials
    settingsJson.remove("ssid");
    settingsJson.remove("password");

    return settingsJson;
}

String Settings::get(const char *name) {
    File settings;
    manager->filesystem->readFile(SPIFFS, FILE_SETTINGS, settings);

    DynamicJsonBuffer jsonBuffer;
    JsonObject& settingsJson = jsonBuffer.parse(settings);
    settings.close();

    String value = settingsJson[name];

    return value;
}

bool Settings::set(const char *name, const char *value) {
    File settings;
    manager->filesystem->readFile(SPIFFS, FILE_SETTINGS, settings);

    DynamicJsonBuffer jsonBuffer;
    JsonObject& settingsJson = jsonBuffer.parse(settings);
    settings.close();

    if(!settingsJson.containsKey(name)) {
        return false;
    }
    
    settingsJson[name] = value;

    String settingsStr;
    settingsJson.printTo(settingsStr);
    return manager->filesystem->writeFile(SPIFFS, FILE_SETTINGS, settingsStr.c_str());
}

void Settings::reset() {
    manager->filesystem->deleteFile(SPIFFS, FILE_SETTINGS);
    manager->filesystem->writeFile(SPIFFS, FILE_SETTINGS, DEFAULT_SETTINGS);
}