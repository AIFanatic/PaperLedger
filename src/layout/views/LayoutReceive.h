#ifndef LAYOUTRECEIVE_H
#define LAYOUTRECEIVE_H

#include "../Render.h"
#include "../Display.h"
#include "../helpers/LayoutBase.h"
#include "../helpers/LayoutList.h"

#include <MenuBackend.h>

class LayoutReceive: public LayoutBase {
    public:
        LayoutReceive(Display *_display);
        ~LayoutReceive(void);

    private:
        void initMenu();
        void showMenu();

        void leftButtonClicked();
        void rightButtonClicked();
        void okButtonClicked();

        static void menuChangeEventStatic(MenuChangeEvent changed, void *context);
        void menuChangeEvent(MenuChangeEvent changed);

        LayoutList *menuList;

        MenuBackend *menuRoot;

        MenuItem wifi_status = MenuItem("Wifi_Status");
        MenuItem wifi_connect = MenuItem("Wifi_Connect");
        MenuItem wifi_disconnect = MenuItem("Wifi_Disconnect");
        MenuItem wifi_back = MenuItem("Wifi_Back");
        MenuItem wifi_back_pressed = MenuItem("Wifi_Back_Pressed");
};

#endif