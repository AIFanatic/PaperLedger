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
        void drawWifi(int rssi, bool hasInternet, bool isInAccessPointMode, bool shouldRender);
        void drawState(const unsigned char *icon, bool shouldRender);


        int lastUpdate = 0;
        int batteryChargePercentage = 0;
        int networkSignalStrength = 0;
        bool networkHasInternet = false;
        bool isInAccessPointMode = false;
        bool isCharging = 0;
        bool isGoingToSleep = 0;

        #define UPDATE_FREQUENCY 5000
};

#endif