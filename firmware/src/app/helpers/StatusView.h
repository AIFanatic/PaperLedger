#ifndef StatusView_H
#define StatusView_H

#include "../Manager.h"

class StatusView {
    public:
        StatusView(Manager *_manager);

        Manager *manager;

        void draw();
        void update();

    private:
        void drawBattery(int percentage, bool shouldRender);
        void updateBattery(bool shouldDraw = false);

        void drawWifi(int rssi, bool hasInternet, bool shouldRender);
        void updateWifi(bool shouldDraw = false);

        int lastUpdate;
        int batteryChargePercentage;
        int networkSignalStrength;
        bool networkHasInternet;

        int temp = 100;

        #define UPDATE_FREQUENCY 5000
};

#endif