#include "DeepSleep.h"

#include "../Manager.h"

DeepSleep::DeepSleep(Manager *_manager) {
    manager = _manager;
};

int DeepSleep::getWakeupCause() {
    return esp_sleep_get_wakeup_cause();
}

bool DeepSleep::hasBootedFromDeepSleep() {
    return (esp_sleep_get_wakeup_cause() != ESP_SLEEP_WAKEUP_UNDEFINED);
}

bool DeepSleep::canEnterDeepSleep() {
    return (Utils::getBootCurrentTime() > minAwakeBootTime);
}
void DeepSleep::enterDeepSleep() {
    if(!canEnterDeepSleep()) {
        return;
    }
    esp_sleep_enable_ext0_wakeup(LEFT_BUTTON, LOW);
    esp_sleep_enable_ext0_wakeup(OK_BUTTON, LOW);
    esp_sleep_enable_ext0_wakeup(RIGHT_BUTTON, LOW);

    esp_deep_sleep_start();
}

void DeepSleep::setMinAwakeBootTimeOffset(long offsetMillis) {
    minAwakeBootTime = Utils::getBootCurrentTime() + offsetMillis;
}

void DeepSleep::update() {

}