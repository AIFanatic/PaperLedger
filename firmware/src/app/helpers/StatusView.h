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
        void drawWifi(int rssi, bool hasInternet, bool shouldRender);
        void drawState(int stateIcon, bool shouldRender);


        int lastUpdate;
        int batteryChargePercentage;
        int networkSignalStrength;
        bool networkHasInternet;
        bool isCharging;
        bool isGoingToSleep;

        #define UPDATE_FREQUENCY 5000
};

#endif