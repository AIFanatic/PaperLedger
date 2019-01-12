#ifndef MANAGER_H
#define MANAGER_H

#include "./Render.h"
#include "../FileSystem.h"
#include "./NetworkManager.h"
#include "./Settings.h"
#include "./Tickers.h"

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
        
    private:
        int currentIndex;

        void *currentLayout;

        bool isInitializingLayout;
};

#endif