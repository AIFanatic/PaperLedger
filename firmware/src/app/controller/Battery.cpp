#include "Battery.h"

#include "../Manager.h"

Battery::Battery(Manager *_manager) {
    manager = _manager;

    isCharging = getIsCharging();
    chargePercentage = getChargePercentage();
}

void Battery::requestBatteryStatus(AsyncWebServerRequest *request) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& response = jsonBuffer.createObject();

    DynamicJsonBuffer batteryStatusBuffer;
    JsonObject& batteryStatus = batteryStatusBuffer.createObject();
    batteryStatus["charging"] = isCharging;
    batteryStatus["percentage"] = chargePercentage;

    DynamicJsonBuffer buffer;
    response["status"] = "ok";
    response["message"] = batteryStatus;

    String str;
    response.printTo(str);
    request->send(200, "application/json", str);
}

bool Battery::getIsCharging() {
    int charge = analogRead(CHARGE_PIN);
    
    return charge > 100 ? false : true;
}

int Battery::getChargePercentage() {
    int vbat = analogRead(VBAT_PIN);

    if(isCharging) {
        vbat -= BATTERY_CHARGE_DIFFERENCE_ADC;
    }

    return constrain(map(vbat, BATTERY_ZERO_CHARGE_ADC, BATTERY_FULL_CHARGE_ADC, 0, 100), 0, 100);
}

void Battery::update() {
    long currentTime = Utils::getCurrentTime();

    if((currentTime - lastUpdate) > BATTERY_CHECK_FREQUENCY) {
        isCharging = getIsCharging();
        chargePercentage = getChargePercentage();

        if(isCharging && chargePercentage <= BATTERY_CHARGED_PERCENTAGE) {
            digitalWrite(RED_LED_PIN, HIGH);
        }
        else {
            digitalWrite(RED_LED_PIN, LOW);
        }

        lastUpdate = currentTime;
    }
}