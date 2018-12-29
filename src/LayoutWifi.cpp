#include "LayoutWifi.h"

LayoutWifi::LayoutWifi(Render *_render) {
    render = _render;

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
}