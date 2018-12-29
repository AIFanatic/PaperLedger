#include "Layout.h"

Layout::Layout(Render *_render) {
    render = _render;
    
    render->clearScreen();
    render->drawFromJson(reinterpret_cast<const char*>(MENU_MAIN));

    initButtons();
    initMenu();
};

Layout::~Layout() {
};

void Layout::initButtons() {
    Serial.println("BUTTONS INIT");

    leftButton = new Pushbutton(LEFT_BUTTON);
    rightButton = new Pushbutton(RIGHT_BUTTON);
    okButton = new Pushbutton(OK_BUTTON);
};

void Layout::leftButtonClicked() {
    menuRoot->moveUp();
    Serial.println("left button clicked");
};

void Layout::rightButtonClicked() {
    menuRoot->moveDown();
    Serial.println("right button clicked");
};

void Layout::okButtonClicked() {
    menuRoot->moveRight();
    Serial.println("ok button clicked");
};

void Layout::updateButtons() {
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

void Layout::update() {
    updateButtons();
}




void Layout::initMenu() {
    menuRoot = new MenuBackend(nullptr, menuChangeEventStatic, this);

	Serial.println("Setting up menu...");
	//add the file menu to the menu root
	menuRoot->getRoot().add(send);
    
    send.addAfter(receive);
    receive.addAfter(setup);

    setup.addRight(wifi);
        //we want looping both up and down
        wifi.addAfter(wallet);
            wifi.addRight(wifi_menu);
        wallet.addAfter(setup_back);
        setup_back.addRight(setup);
}

void Layout::menuChangeEventStatic(MenuChangeEvent changed, void *context) {
    Layout *instance = (Layout *)context;
    instance->menuChangeEvent(changed);
}

void Layout::menuChangeEvent(MenuChangeEvent changed) {
	Serial.print("Menu change ");
	Serial.print(changed.from.getName());
	Serial.print(" ");
	Serial.println(changed.to.getName());

    if(strcmp(changed.to.getName(), "Send") == 0) {
        render->drawFromJson(reinterpret_cast<const char*>(MENU_SEND));
    }
    else if(strcmp(changed.to.getName(), "Receive") == 0) {
        render->drawFromJson(reinterpret_cast<const char*>(MENU_RECEIVE));
    }
    else if(strcmp(changed.to.getName(), "Setup") == 0) {
        render->drawFromJson(reinterpret_cast<const char*>(MENU_SETUP));
    }
    else if(strcmp(changed.to.getName(), "Wifi") == 0) {
        render->drawFromJson(reinterpret_cast<const char*>(MENU_WIFI));
    }
    else if(strcmp(changed.to.getName(), "Wifi_Menu") == 0) {
        render->drawFromJson(reinterpret_cast<const char*>(MENU_WIFI)); // Have to show since LayoutList will update the frame

        new LayoutWifi(render);
    }
    else if(strcmp(changed.to.getName(), "Wallet") == 0) {
        render->drawFromJson(reinterpret_cast<const char*>(MENU_WALLET));
    }
    else if(strcmp(changed.to.getName(), "Back") == 0) {
        render->drawFromJson(reinterpret_cast<const char*>(MENU_BACK));
    }
}