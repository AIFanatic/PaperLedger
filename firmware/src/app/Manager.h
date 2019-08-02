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

#include "./helpers/RTC.h"

class Manager {
    public:
        Manager();
        ~Manager(void);

        void update();
        void show(int index);
        void *getCurrentView();
        void enterDeepSleep();

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
        void loadView();

        void setCurrentViewIndex(int value) { RTC::write(RTC_STORAGE::CURRENT_VIEW_INDEX, value); }
        int getCurrentViewIndex() { return RTC::read(RTC_STORAGE::CURRENT_VIEW_INDEX); }

        void *currentView;

        bool isInitializingLayout;
};

#endif