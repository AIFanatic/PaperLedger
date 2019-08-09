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

void StatusView::drawWifi(int rssi, bool hasInternet, bool shouldRender) {
    int x = 250;
    int y = 10;

    manager->render->drawCircle(x, y, 3, BLACK, hasInternet);

    if (rssi >= 0) return;

    int WIFIsignal = 0;
    for (int _rssi = -100; _rssi <= rssi; _rssi = _rssi + 20) {
        if (_rssi <= -33)  WIFIsignal = 8;
        if (_rssi <= -66)  WIFIsignal = 6;
        if (_rssi <= -100)  WIFIsignal = 4;

        int start_angle = 50; // Arc size left
        int end_angle   =  130; // Arc size right
        for (int i = start_angle; i < end_angle; i++) {
            int pX = x + cos((i-90)*3.14/180) * WIFIsignal*1.6;
            int pY = y + sin((i-90)*3.14/180) * WIFIsignal*1.6;
            manager->render->drawPixel(pX, pY, BLACK);
        }
    }

    if(shouldRender) {
        manager->render->draw(x-10, y-10, 30, 30, true);
    }
}

void StatusView::drawState(int stateIcon, bool shouldRender) {
    int x = 5;
    int y = 5;
    manager->render->drawImage(stateIcon, x, y, 16, 16, BLACK, 0);
    if(shouldRender) {
        manager->render->draw(x, y, 16, 16, true);
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

        if(networkHasInternet != currentNetworkHasInternetAccess ||
        abs(Utils::diff(networkSignalStrength, currentNetworkSignalStrength)) > 33) {

            networkSignalStrength = currentNetworkSignalStrength;
            networkHasInternet = manager->webserver->hasInternetAccess;

            drawWifi(networkSignalStrength, networkHasInternet, true);
        }

        // Status
        bool currentIsCharging = manager->battery->isCharging;

        if(isCharging != currentIsCharging) {
            isCharging = currentIsCharging;
            if(isCharging) {
                drawState(10, true);
            }
            else {
                drawState(13, true);
            }
        }

        lastUpdate = currentTime;
    }

    if(manager->deepSleep->isGoingToDeepSleep() && !isGoingToSleep) {
        isGoingToSleep = manager->deepSleep->isGoingToDeepSleep();
        drawState(11, true);
    }
}

void StatusView::draw() {
    batteryChargePercentage = manager->battery->chargePercentage;
    drawBattery(batteryChargePercentage, false);

    networkSignalStrength = manager->webserver->getWifiSignal();
    networkHasInternet = manager->webserver->hasInternetAccess;
    drawWifi(networkSignalStrength, networkHasInternet, false);

    isGoingToSleep = manager->deepSleep->isGoingToDeepSleep();
    isCharging = manager->battery->isCharging;
    if (isGoingToSleep) {
        drawState(11, false);
    }
    else if(isCharging) {
        drawState(10, false);
    }
    else {
        drawState(13, false);
    }
}