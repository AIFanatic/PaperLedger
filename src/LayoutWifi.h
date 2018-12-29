#ifndef LAYOUTWIFI_H
#define LAYOUTWIFI_H

#include <Render.h>
#include <MenuBackend.h>
#include <LayoutList.h>

class LayoutWifi {
    public:
        LayoutWifi(Render *render);
        ~LayoutWifi(void);

        void draw();

    private:
        void initMenu();
        void showMenu();

        static void menuChangeEventStatic(MenuChangeEvent changed, void *context);
        void menuChangeEvent(MenuChangeEvent changed);

        Render *render;
        LayoutList *menuList;

        MenuBackend *menuRoot;

        MenuItem wifi_status = MenuItem("Wifi_Status");
        MenuItem wifi_connect = MenuItem("Wifi_Connect");
        MenuItem wifi_disconnect = MenuItem("Wifi_Disconnect");
};

#endif