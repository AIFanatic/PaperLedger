#include "LayoutSetup.h"

LayoutSetup::LayoutSetup(Manager *_manager): LayoutBase(_manager) {
    initMenu();
    
    showMenu(MAIN_MENU, SIZEOFARRAY(MAIN_MENU));
};

LayoutSetup::~LayoutSetup() {
};

void LayoutSetup::initMenu() {
    // Init list
    menuList = new LayoutList(manager->render);
    menuList->init(0, 0, 296, 125, 12, BLACK);
}

void LayoutSetup::showMenu(const char *menu[][2], int size) {
    menuList->removeAll();
    menuList->addFromArray(menu, size);

    menuList->setActive(0);
}

void LayoutSetup::leftButtonClicked() {
    Serial.println("left button clicked");

    menuList->moveUp();
};

void LayoutSetup::rightButtonClicked() {
    Serial.println("right button clicked");

    menuList->moveDown();
};

void LayoutSetup::okButtonClicked() {
    const char *active = menuList->getActiveIdentifier();

    Serial.print(active);
    Serial.println(" clicked");

    if(strcmp(active, "NETWORK") == 0) {
    }
    else if(strcmp(active, "RESET") == 0) {
        showMenu(RESET_MENU, SIZEOFARRAY(RESET_MENU));
    }
    else if(strcmp(active, "RESET_TICKERS") == 0) {
        manager->tickers->reset();
    }
    else if(strcmp(active, "RESET_SETTINGS") == 0) {
        manager->settings->reset();
    }
    else if(strcmp(active, "RESET_FACTORY") == 0) {
        manager->tickers->reset();
        manager->settings->reset();
    }
    else if(strcmp(active, "RESET_BACK") == 0) {
        showMenu(MAIN_MENU, SIZEOFARRAY(MAIN_MENU));
    }
    else if(strcmp(active, "BACK") == 0) {
        manager->show(LAYOUT_TICKER);
    }
};