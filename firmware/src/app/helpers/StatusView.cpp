#include "StatusView.h"

StatusView::StatusView(Manager *_manager) {
    manager = _manager;
};

void StatusView::drawBattery(int percentage, bool shouldRender) {
    int x = 270;
    int y = 5;

    manager->render->drawRectangle(x + 3, y, 19, 10, BLACK, 0);
    manager->render->drawRectangle(x + 22, y + 2, 2, 5, BLACK, 1);
    manager->render->drawRectangle(x + 5, y + 2, 15, 6, WHITE, 1);
    manager->render->drawRectangle(x + 5, y + 2, 15 * percentage / 100.0, 6, BLACK, 1);

    if(shouldRender) {
        manager->render->draw(x, y, 22, 15, true);
    }
}

void StatusView::drawWifi(int rssi, bool hasInternet, bool isInAccessPointMode, bool shouldRender) {
    int x = 250;
    int y = 10;

    manager->render->drawRectangle(x-17, y-10, 35, 20, WHITE, true);
    manager->render->drawCircle(x, y, 3, BLACK, hasInternet);

    if(isInAccessPointMode) {
        manager->render->drawArc(x, y, 50, 130, 7, BLACK);
        manager->render->drawArc(x, y, 50, 130, 11, BLACK);
        manager->render->drawArc(x, y, 50, 130, 15, BLACK);

        manager->render->drawArc(x, y, 230, 310, 7, BLACK);
        manager->render->drawArc(x, y, 230, 310, 11, BLACK);
        manager->render->drawArc(x, y, 230, 310, 15, BLACK);
    }

    if (hasInternet) {
        if(rssi > -100) manager->render->drawArc(x, y, 50, 130, 7, BLACK);
        if(rssi > -66) manager->render->drawArc(x, y, 50, 130, 11, BLACK);
        if(rssi > -33) manager->render->drawArc(x, y, 50, 130, 15, BLACK);
    }

    if(shouldRender) {
        manager->render->draw(x-15, y-10, 50, 50, true);
    }
}

void StatusView::drawState(const unsigned char *icon, bool shouldRender) {
    int x = 5;
    int y = 5;
    manager->render->drawRectangle(x, y, 16, 16, WHITE, 1);
    manager->render->drawImage(icon, x, y, 16, 16, BLACK);
    if(shouldRender) {
        manager->render->draw(x, y, 20, 20, true);
    }
}

void StatusView::update() {
    long currentTime = Utils::getCurrentTime();

    if((currentTime - lastUpdate) > UPDATE_FREQUENCY) {
        // Battery
        int currentBatteryChargePercentage = manager->battery->chargePercentage;
        if(abs(Utils::diff(batteryChargePercentage, currentBatteryChargePercentage)) > 10) {
            batteryChargePercentage = currentBatteryChargePercentage;
            drawBattery(batteryChargePercentage, true);
        }
        
        // Wifi
        int currentNetworkSignalStrength = manager->webserver->getWifiSignal();
        bool currentNetworkHasInternetAccess = manager->webserver->hasInternetAccess;
        bool currentIsInAccessPointMode = manager->webserver->getWifiMode() == WIFI_MODE_AP;

        if(networkHasInternet != currentNetworkHasInternetAccess ||
        isInAccessPointMode != currentIsInAccessPointMode ||
        abs(Utils::diff(networkSignalStrength, currentNetworkSignalStrength)) > 33) {

            networkSignalStrength = currentNetworkSignalStrength;
            networkHasInternet = currentNetworkHasInternetAccess;
            isInAccessPointMode = currentIsInAccessPointMode;

            drawWifi(networkSignalStrength, networkHasInternet, isInAccessPointMode, true);
        }

        // Status
        bool currentIsCharging = manager->battery->isCharging;

        if(isCharging != currentIsCharging) {
            isCharging = currentIsCharging;
            if(isCharging) {
                drawState(ICON_BOLT_16, true);
            }
        }

        lastUpdate = currentTime;
    }

    if(manager->deepSleep->isGoingToDeepSleep() && !isGoingToSleep) {
        isGoingToSleep = manager->deepSleep->isGoingToDeepSleep();
        drawState(ICON_SLEEP_16, true);
    }
}

void StatusView::draw() {
    batteryChargePercentage = manager->battery->chargePercentage;
    drawBattery(batteryChargePercentage, false);

    networkSignalStrength = manager->webserver->getWifiSignal();
    networkHasInternet = manager->webserver->hasInternetAccess;
    isInAccessPointMode = manager->webserver->getWifiMode() == WIFI_MODE_AP;
    drawWifi(networkSignalStrength, networkHasInternet, isInAccessPointMode, false);

    isGoingToSleep = manager->deepSleep->isGoingToDeepSleep();
    isCharging = manager->battery->isCharging;
    if (isGoingToSleep) {
        drawState(ICON_SLEEP_16, false);
    }
    else if(isCharging) {
        drawState(ICON_BOLT_16, false);
    }
}