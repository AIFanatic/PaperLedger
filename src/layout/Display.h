// TODO: Rename to Manager or something
#ifndef DISPLAY_H
#define DISPLAY_H

#include "./Render.h"
#include "../Wallet.h"
#include "../FileSystem.h"
#include "../menus.h"

class Display {
    public:
        Display();
        ~Display(void);

        void update();

        void show(int index);
        
        Render *render;
        Wallet *wallet;
        FileSystem *filesystem;

    private:
        int currentIndex;

        void *currentDisplay;
};

#endif