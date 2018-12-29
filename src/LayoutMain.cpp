#include "LayoutMain.h"

LayoutMain::LayoutMain(Render *_render, void *_display) {
    render = _render;
    display = _display;
    
    render->clearScreen();
    render->drawFromJson(reinterpret_cast<const char*>(MENU_MAIN));

    initButtons();
    initMenu();
};

LayoutMain::~LayoutMain() {
};

void LayoutMain::initButtons() {
    Serial.println("BUTTONS INIT");

    leftButton = new Pushbutton(LEFT_BUTTON);
    rightButton = new Pushbutton(RIGHT_BUTTON);
    okButton = new Pushbutton(OK_BUTTON);
};

void LayoutMain::leftButtonClicked() {
    menuRoot->moveUp();
    Serial.println("MAIN - left button clicked");
};

void LayoutMain::rightButtonClicked() {
    menuRoot->moveDown();
    Serial.println("right button clicked");
};

void LayoutMain::okButtonClicked() {
    menuRoot->moveRight();
    Serial.println("ok button clicked");
};

void LayoutMain::updateButtons() {
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

void LayoutMain::update() {
    updateButtons();
}




void LayoutMain::initMenu() {
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

void LayoutMain::menuChangeEventStatic(MenuChangeEvent changed, void *context) {
    LayoutMain *instance = (LayoutMain *)context;
    instance->menuChangeEvent(changed);
}

void LayoutMain::menuChangeEvent(MenuChangeEvent changed) {
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

        (reinterpret_cast<Display *>(display))->show(1);
    }
    else if(strcmp(changed.to.getName(), "Wallet") == 0) {
        render->drawFromJson(reinterpret_cast<const char*>(MENU_WALLET));
    }
    else if(strcmp(changed.to.getName(), "Back") == 0) {
        render->drawFromJson(reinterpret_cast<const char*>(MENU_BACK));
    }
}