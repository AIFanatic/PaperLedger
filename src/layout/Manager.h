// TODO: Rename to Manager or something
#ifndef MANAGER_H
#define MANAGER_H

#include "./Render.h"
#include "../FileSystem.h"
#include "../menus.h"

class Manager {
    public:
        Manager();
        ~Manager(void);

        void update();

        void show(int index);
        
        Render *render;
        FileSystem *filesystem;

    private:
        int currentIndex;

        void *currentLayout;
};

#endif