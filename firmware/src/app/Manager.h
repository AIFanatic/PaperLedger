#ifndef MANAGER_H
#define MANAGER_H

#include "./controller/Render.h"
#include "./controller/FileSystem.h"
#include "./controller/WebServer.h"
#include "./controller/Settings.h"
#include "./controller/Tickers.h"
#include "./controller/Alarms.h"
#include "./controller/Speaker.h"
#include "./controller/Updater.h"
#include "./controller/Battery.h"

#include "../variables.h"

class Manager {
    public:
        Manager();
        ~Manager(void);

        void update();
        void show(int index);
        int getCurrentIndex();
        void *getCurrentView();

        Render *render;
        FileSystem *filesystem;
        WebServer *webserver;
        
        Settings *settings;
        Tickers *tickers;
        Alarms *alarms;
        SPEAKER *speaker;
        Updater *updater;
        Battery *battery;
        
    private:
        int currentIndex;

        void *currentView;

        bool isInitializingLayout;
};

#endif