#include "LayoutWifi.h"

LayoutWifi::LayoutWifi(Render *_render, void *_display): LayoutBase(_render, _display) {
    initMenu();
    showMenu();
};

LayoutWifi::~LayoutWifi() {
};

void LayoutWifi::initMenu() {
    menuRoot = new MenuBackend(nullptr, menuChangeEventStatic, this);
    
    menuRoot->getRoot().add(wifi_status);
    wifi_status.addAfter(wifi_connect);
    wifi_connect.addAfter(wifi_disconnect);
    wifi_disconnect.addAfter(wifi_back);
        wifi_back.addRight(wifi_back_pressed);

    // wrap
    wifi_status.addBefore(wifi_back);
    wifi_back.addAfter(wifi_status);
}

void LayoutWifi::showMenu() {
    menuList = new LayoutList(render);
    menuList->init(130, 0, 156, 72, 12);
    menuList->add("Status");
    menuList->add("Connect");
    menuList->add("Disconnect");
    menuList->add("Back");
    menuList->draw();
}

void LayoutWifi::menuChangeEventStatic(MenuChangeEvent changed, void *context) {
    LayoutWifi *instance = (LayoutWifi *)context;
    instance->menuChangeEvent(changed);
}

void LayoutWifi::menuChangeEvent(MenuChangeEvent changed) {
	Serial.print("Menu change ");
	Serial.print(changed.from.getName());
	Serial.print(" ");
	Serial.println(changed.to.getName());

    if(strcmp(changed.to.getName(), "Wifi_Status") == 0) {
        menuList->setActive(0);
    }
    else if(strcmp(changed.to.getName(), "Wifi_Connect") == 0) {
        menuList->setActive(1);
    }
    else if(strcmp(changed.to.getName(), "Wifi_Disconnect") == 0) {
        menuList->setActive(2);
    }
    else if(strcmp(changed.to.getName(), "Wifi_Back") == 0) {
        menuList->setActive(3);
    }
    else if(strcmp(changed.to.getName(), "Wifi_Back_Pressed") == 0) {
        (reinterpret_cast<Display *>(display))->show(0);
    }
}




void LayoutWifi::leftButtonClicked() {
    menuRoot->moveUp();
    Serial.println("WIFI - left button clicked");
};

void LayoutWifi::rightButtonClicked() {
    menuRoot->moveDown();
    Serial.println("right button clicked");
};

void LayoutWifi::okButtonClicked() {
    menuRoot->moveRight();
    Serial.println("ok button clicked");
};