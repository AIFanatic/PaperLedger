#ifndef LAYOUTWIFI_H
#define LAYOUTWIFI_H

#include <Render.h>
#include <Pushbutton.h>
#include <MenuBackend.h>
#include <LayoutList.h>

#include "menus.h"

class LayoutWifi {
    public:
        LayoutWifi(Render *render, void *_display);
        ~LayoutWifi(void);

        void draw();
        
        void update();

    private:
        void initMenu();
        void showMenu();

        void initButtons();
        void updateButtons();

        void leftButtonClicked();
        void rightButtonClicked();
        void okButtonClicked();

        static void menuChangeEventStatic(MenuChangeEvent changed, void *context);
        void menuChangeEvent(MenuChangeEvent changed);

        Render *render;
        void *display;
        
        LayoutList *menuList;

        MenuBackend *menuRoot;

        MenuItem wifi_status = MenuItem("Wifi_Status");
        MenuItem wifi_connect = MenuItem("Wifi_Connect");
        MenuItem wifi_disconnect = MenuItem("Wifi_Disconnect");

        Pushbutton *leftButton;
        Pushbutton *rightButton;
        Pushbutton *okButton;
};

#endif