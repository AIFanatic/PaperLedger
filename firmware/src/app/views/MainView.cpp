#include "MainView.h"

MainView::MainView(Manager *_manager): LayoutBase(_manager) {
    showMenu();
};

MainView::~MainView() {
};

void MainView::showMenu() {
    manager->render->fillScreen(1);
    manager->render->drawRectangle(85, 4, 130, 120, BLACK, 0);

    if(currentMenu == WALLET) {
        manager->render->drawImage(8, 115, 15, 64, 64, BLACK, 2);
        manager->render->drawText(0, 115, "Wallet", 18, BLACK, CENTER_ALIGNMENT);

        manager->render->drawRectangle(100, 44, 100, 15, BLACK, 1);
        manager->render->drawText(0, 55, "Coming soon", 7, WHITE, CENTER_ALIGNMENT);
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

    draw();
};

void MainView::leftButtonClicked() {
    if(currentMenu != WALLET) {
        currentMenu--;
    }

    showMenu();
};

void MainView::rightButtonClicked() {
    if(currentMenu != SETUP) {
        currentMenu++;
    }

    showMenu();
};

void MainView::okButtonClicked() {
    if(currentMenu == WALLET) {
    }
    else if(currentMenu == TICKERS) {
        manager->show(TICKER_VIEW);
    }
    else if(currentMenu == SETUP) {
        manager->show(SETUP_VIEW);
    }
};