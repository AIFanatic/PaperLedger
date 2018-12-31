#include "LayoutReceive.h"

LayoutReceive::LayoutReceive(Display *_display): LayoutBase(_display) {
    initMenu();
    showMenu();
};

LayoutReceive::~LayoutReceive() {
};

void LayoutReceive::initMenu() {
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

void LayoutReceive::showMenu() {
    // Get balances from wallet
    // TODO: Is DynamicJsonBuffer a performance enemy?
    // And String btw
    DynamicJsonBuffer jsonBuffer;
    JsonVariant balances = display->wallet->getBalances();
    
    for(int i = 0; i < balances.size(); i++) {
        String params = balances[i];
        // JsonVariant entry = jsonBuffer.parse(params);

        // String name = entry["name"];
        // String balance = entry["balance"];

        Serial.println(params);
        // Serial.println(balance);
    }
    

    menuList = new LayoutList(display->render);
    menuList->init(128, 32, 160, 80, 9, BLACK);
    menuList->add("Status");
    menuList->add("Connect");
    menuList->add("Disconnect");
    menuList->add("Back");
    menuList->draw();
    
    // Move from root to first menu
    menuRoot->moveDown();
}

void LayoutReceive::menuChangeEventStatic(MenuChangeEvent changed, void *context) {
    LayoutReceive *instance = (LayoutReceive *)context;
    instance->menuChangeEvent(changed);
}

void LayoutReceive::menuChangeEvent(MenuChangeEvent changed) {
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
        display->show(LAYOUT_MAIN);
    }
}




void LayoutReceive::leftButtonClicked() {
    menuRoot->moveUp();
    Serial.println("WIFI - left button clicked");
};

void LayoutReceive::rightButtonClicked() {
    menuRoot->moveDown();
    Serial.println("right button clicked");
};

void LayoutReceive::okButtonClicked() {
    menuRoot->moveRight();
    Serial.println("ok button clicked");
};