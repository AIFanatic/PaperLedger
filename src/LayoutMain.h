#ifndef LAYOUTMAIN_H
#define LAYOUTMAIN_H

#include <Render.h>
#include <Display.h>
#include <LayoutBase.h>
#include <MenuBackend.h>

#include "menus.h"

class LayoutMain: public LayoutBase {
    public:
        LayoutMain(Render *render, void *_display);
        ~LayoutMain(void);

    private:
        void initMenu();

        void leftButtonClicked();
        void rightButtonClicked();
        void okButtonClicked();
        
        static void menuChangeEventStatic(MenuChangeEvent changed, void *context);
        void menuChangeEvent(MenuChangeEvent changed);

        MenuBackend *menuRoot;

        MenuItem send = MenuItem("Send");
        
        MenuItem receive = MenuItem("Receive");

        MenuItem setup = MenuItem("Setup");
            MenuItem wifi = MenuItem("Wifi");
                MenuItem wifi_menu = MenuItem("Wifi_Menu");
            MenuItem wallet = MenuItem("Wallet");
            MenuItem setup_back = MenuItem("Back");
};

#endif