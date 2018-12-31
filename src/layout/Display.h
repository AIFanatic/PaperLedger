#ifndef DISPLAY_H
#define DISPLAY_H

#include "./Render.h"
#include "../menus.h"

class Display {
    public:
        Display(Render *render);
        ~Display(void);

        void update();

        void show(int index);

    private:
        Render *render;

        int currentIndex;

        void *currentDisplay;
};

#endif