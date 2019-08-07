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

bool DeepSleep::isGoingToDeepSleep() {
    return needDeepSleep;
}

bool DeepSleep::canEnterDeepSleep() {
    if(Utils::getBootCurrentTime() <= minAwakeBootTime) {
        return false;
    }

    // if(manager->battery->isCharging) {
    //     return false;
    // }
    
    return true;
}
void DeepSleep::enterDeepSleep() {
    if(!canEnterDeepSleep()) {
        return;
    }

    needDeepSleep = true;
}

void DeepSleep::setMinAwakeBootTimeOffset(long offsetMillis) {
    minAwakeBootTime = Utils::getBootCurrentTime() + offsetMillis;
}

void DeepSleep::update() {
    if(needDeepSleep) {
        if(sleepCountdown > 0) {
            sleepCountdown--;
            return;
        }
        esp_sleep_enable_ext0_wakeup(LEFT_BUTTON, LOW);
        esp_sleep_enable_ext0_wakeup(OK_BUTTON, LOW);
        esp_sleep_enable_ext0_wakeup(RIGHT_BUTTON, LOW);
        esp_deep_sleep_start();
    }
}