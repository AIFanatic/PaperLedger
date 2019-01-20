#include "LayoutMain.h"

LayoutMain::LayoutMain(Manager *_manager): LayoutBase(_manager) {
    showMenu();
};

LayoutMain::~LayoutMain() {
};

void LayoutMain::showMenu() {
    manager->render->fillScreen(1);
    manager->render->drawRectangle(85, 4, 130, 120, BLACK, 0);

    if(currentMenu == WALLET) {
        manager->render->drawImage(8, 115, 15, 64, 64, BLACK, 2);
        manager->render->drawText(0, 115, "Wallet", 18, BLACK, CENTER_ALIGNMENT);
    }
    else if(currentMenu == TICKERS) {
        manager->render->drawImage(9, 115, 15, 64, 64, BLACK, 2);
        manager->render->drawText(0, 115, "Tickers", 18, BLACK, CENTER_ALIGNMENT);
    }
    else if(currentMenu == SETUP) {
        manager->render->drawImage(7, 115, 15, 64, 64, BLACK, 2);
        manager->render->drawText(0, 115, "Setup", 18, BLACK, CENTER_ALIGNMENT);
    }

    if(currentMenu != WALLET) {
        manager->render->drawImage(1, 5, 32, 64, 64, BLACK, 1);
    }

    if(currentMenu != SETUP) {
        manager->render->drawImage(0, 225, 32, 64, 64, BLACK, 1);
    }

    manager->render->draw();

    // for(int i = 35; i < 255; i++) {
    //     manager->render->fillScreen(1);
    //     manager->render->drawText(0, 115, "A", (char)i, 18, BLACK, CENTER_ALIGNMENT);
    //     Serial.printf("%c %i\n", (char)i, i);

    //     manager->render->draw();
    //     delay(1000);
    // }
};

void LayoutMain::leftButtonClicked() {
    Serial.println("left");
    if(currentMenu != WALLET) {
        currentMenu--;
    }

    showMenu();
};

void LayoutMain::rightButtonClicked() {
    Serial.println("right");
    if(currentMenu != SETUP) {
        currentMenu++;
    }

    showMenu();
};

void LayoutMain::okButtonClicked() {
    if(currentMenu == WALLET) {
    }
    else if(currentMenu == TICKERS) {
        manager->show(LAYOUT_TICKER);
    }
    else if(currentMenu == SETUP) {
        manager->show(LAYOUT_SETUP);
    }
};