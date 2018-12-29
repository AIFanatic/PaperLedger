#ifndef DISPLAY_H
#define DISPLAY_H

#include <Render.h>
#include <LayoutMain.h>
#include <LayoutWifi.h>

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

        enum DISPLAYS {
            LAYOUT_MAIN,
            LAYOUT_WIFI
        };
};

#endif