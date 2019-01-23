#ifndef MANAGER_H
#define MANAGER_H

#include "./Render.h"
#include "../FileSystem.h"
#include "./NetworkManager.h"
#include "./Settings.h"
#include "./Tickers.h"
#include "../Speaker.h"

#include "../variables.h"

class Manager {
    public:
        Manager();
        ~Manager(void);

        void update();

        void show(int index);

        Render *render;
        FileSystem *filesystem;
        NetworkManager *networkManager;
        
        Settings *settings;
        Tickers *tickers;

        SPEAKER *speaker;
        
    private:
        int currentIndex;

        void *currentLayout;

        bool isInitializingLayout;
};

#endif