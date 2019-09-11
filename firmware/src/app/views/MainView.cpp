#include "MainView.h"

MainView::MainView(Manager *_manager): LayoutBase(_manager) {
    showMenu();
    
    if(!manager->webserver->hasInternetAccess && manager->webserver->getWifiMode() != WIFI_MODE_AP) {
        manager->webserver->needNetworkReconnect = true;
    }
};

MainView::~MainView() {
    Serial.printf("MainView destroyed\n");
}

void MainView::showMenu() {
    manager->render->fillScreen(1);
    manager->render->drawRectangle(85, 4, 130, 120, BLACK, 0);

    if(currentMenu == WALLET) {
        manager->render->drawImage(ICON_WALLET_64, 115, 15, 64, 64, BLACK);
        manager->render->drawText(0, 115, "Wallet", 18, BLACK, CENTER_ALIGNMENT);

        manager->render->drawRectangle(100, 44, 100, 15, BLACK, true);
        manager->render->drawText(0, 55, "Coming soon", 7, WHITE, CENTER_ALIGNMENT);
    }
    else if(currentMenu == TICKERS) {
        manager->render->drawImage(ICON_CHART_64, 115, 15, 64, 64, BLACK);
        manager->render->drawText(0, 115, "Tickers", 18, BLACK, CENTER_ALIGNMENT);
    }
    else if(currentMenu == SETUP) {
        manager->render->drawImage(ICON_SETTINGS_64, 115, 15, 64, 64, BLACK);
        manager->render->drawText(0, 115, "Setup", 18, BLACK, CENTER_ALIGNMENT);
    }

    if(currentMenu != SETUP) {
        manager->render->drawImage(ICON_LEFT_ARROW_64, 225, 32, 64, 64, BLACK);
    }

    if(currentMenu != WALLET) {
        manager->render->drawImage(ICON_RIGHT_ARROW_64, 5, 32, 64, 64, BLACK);
    }

    statusView->draw();
    manager->render->draw();
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

void MainView::update() {
    LayoutBase::update();
    
    statusView->update();
};