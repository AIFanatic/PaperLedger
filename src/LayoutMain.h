#ifndef LAYOUTMAIN_H
#define LAYOUTMAIN_H

#include <Render.h>
#include <Display.h>
#include <MenuBackend.h>
#include <Pushbutton.h>

#include "menus.h"

class LayoutMain {
    public:
        LayoutMain(Render *render, void *_display);
        ~LayoutMain(void);

        void update();

    private:
        void initMenu();
        void initButtons();
        void updateButtons();

        void leftButtonClicked();
        void rightButtonClicked();
        void okButtonClicked();

        Render *render;
        void *display;

        Pushbutton *leftButton;
        Pushbutton *rightButton;
        Pushbutton *okButton;
        
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