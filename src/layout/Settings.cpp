#include "Settings.h"

#include "Manager.h"

Settings::Settings(Manager *_manager) {
    manager = _manager;

    File settings;
    manager->filesystem->readFile(SPIFFS, FILE_SETTINGS, settings);

    DynamicJsonBuffer jsonBuffer;
    JsonObject& settingsJson = jsonBuffer.parse(settings);
    settings.close();

    bool validSSID = settingsJson["ssid"].is<const char *>();
    bool validPassword = settingsJson["password"].is<const char *>();
    
    if(!validSSID || !validPassword) {
        Serial.print("Settings.json is not valid");

        settingsJson["ssid"] = "";
        settingsJson["password"] = "";

        String settingsStr;
        settingsJson.printTo(settingsStr);
        manager->filesystem->writeFile(SPIFFS, FILE_SETTINGS, settingsStr.c_str());

        Serial.print("Created settings.json");
    }
};

Settings::~Settings() {
};

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

    settingsJson[name] = value;

    String settingsStr;
    settingsJson.printTo(settingsStr);
    manager->filesystem->writeFile(SPIFFS, FILE_SETTINGS, settingsStr.c_str());
}

void Settings::reset() {
    manager->filesystem->deleteFile(SPIFFS, FILE_SETTINGS);
}