#ifndef LAYOUT_H
#define LAYOUT_H

#include <Render.h>
#include <MenuBackend.h>
#include <Pushbutton.h>
#include <LayoutList.h>
#include <LayoutWifi.h>

#include "menus.h"

#define LEFT_BUTTON GPIO_NUM_37
#define RIGHT_BUTTON GPIO_NUM_39
#define OK_BUTTON GPIO_NUM_38

class Layout {
    public:
        Layout(Render *render);
        ~Layout(void);

        void update();

    private:
        void initButtons();
        void initMenu();
        void updateButtons();

        void leftButtonClicked();
        void rightButtonClicked();
        void okButtonClicked();

        Render *render;

        LayoutList *activeList;

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