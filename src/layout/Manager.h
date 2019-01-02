#ifndef MANAGER_H
#define MANAGER_H

#include "./Render.h"
#include "../FileSystem.h"
#include "./RequestManager.h"
#include "./Utils.h"
#include "./Settings.h"

#include "../menus.h"

class Manager {
    public:
        Manager();
        ~Manager(void);

        void connectNetwork();

        void update();

        void show(int index);

        void reset();

        Utils *utils;
        Render *render;
        FileSystem *filesystem;
        RequestManager *requestManager;
        Settings *settings;

    private:
        int currentIndex;

        void *currentLayout;

        bool isInitializingLayout;
};

#endif