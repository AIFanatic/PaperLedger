#include "LayoutWifi.h"

LayoutWifi::LayoutWifi(Render *_render, void *_display) {
    render = _render;
    display = _display;

    initMenu();
    initButtons();
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







void LayoutWifi::initButtons() {
    Serial.println("BUTTONS INIT");

    leftButton = new Pushbutton(LEFT_BUTTON);
    rightButton = new Pushbutton(RIGHT_BUTTON);
    okButton = new Pushbutton(OK_BUTTON);
};

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

void LayoutWifi::updateButtons() {
    if (leftButton->getSingleDebouncedPress()) {
        leftButtonClicked();
    }
    if (rightButton->getSingleDebouncedPress()) {
        rightButtonClicked();
    }
    if (okButton->getSingleDebouncedPress()) {
        okButtonClicked();
    }
}

void LayoutWifi::update() {
    updateButtons();
}