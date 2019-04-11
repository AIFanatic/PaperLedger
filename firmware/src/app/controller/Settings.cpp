#include "Settings.h"

#include "../Manager.h"

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

String Settings::get() {
    File settings;
    manager->filesystem->readFile(SPIFFS, FILE_SETTINGS, settings);

    DynamicJsonBuffer jsonBuffer;
    JsonObject& settingsJson = jsonBuffer.parse(settings);
    settings.close();

    String str;
    settingsJson.printTo(str);

    return str;
}

String Settings::get(const char *name) {
    String settings = get();
    DynamicJsonBuffer jsonBuffer;
    JsonObject& settingsJson = jsonBuffer.parse(settings);

    String value = settingsJson[name];

    return value;
}

bool Settings::set(const char *name, const char *value) {
    String settings = get();
    DynamicJsonBuffer jsonBuffer;
    JsonObject& settingsJson = jsonBuffer.parse(settings);

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

void Settings::requestSettings(AsyncWebServerRequest *request) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& response = jsonBuffer.createObject();

    String settingsStr = get();
    DynamicJsonBuffer settingsBuffer;
    JsonObject& settings = settingsBuffer.parse(settingsStr);
    
    // Remove wifi credentials
    settings.remove("ssid");
    settings.remove("password");

    DynamicJsonBuffer buffer;
    response["status"] = "ok";
    response["message"] = settings;

    String str;
    response.printTo(str);
    request->send(200, "application/json", str);
}

void Settings::requestChangeSettings(AsyncWebServerRequest *request) {
    if(!request->hasParam("name", true) || !request->hasParam("value", true)) {
        manager->webserver->requestInvalid(request);
        return;
    }

    const char *name = request->getParam("name", true)->value().c_str();
    const char *value = request->getParam("value", true)->value().c_str();

    bool changed = manager->settings->set(name, value);
    if(false == changed) {
        manager->webserver->requestInvalid(request);
        return;
    }

    request->send(200, "application/json", "{\"status\":\"ok\",\"message\":\"updated setting\"}");
}