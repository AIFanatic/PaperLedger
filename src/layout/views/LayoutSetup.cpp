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
    menuList->init(0, 0, 296, 125, 9, BLACK);
}

void LayoutSetup::showMenu(String menu[][2], int size) {
    menuList->removeAll();
    menuList->addFromArray(menu, size);

    menuList->setActive(0);
}

void LayoutSetup::showStatusMenu() {
    String internet = "Internet: ";
    String networkName = "Network name: " + manager->networkManager->getWifiSSID();
    String networkSignal = "Network signal: " + String(manager->networkManager->getWifiSignal()) + " dBm";
    String networkIP = "Network IP: " + manager->networkManager->getWifiIP();
    String networkMode = "Network mode: Station";
    String freeHeap = "Free ram: " + String(ESP.getFreeHeap()/1000) + " KB";

    if(manager->networkManager->getWifiMode() == WIFI_AP) {
        networkName = "Network name: " + String(AP_NAME);
        networkMode = "Network mode: Access point";
    }

    internet += (manager->networkManager->hasInternetAccess) ? "Yes" : "No";

    String STATUS_MENU[7][2] = 
    {
        {internet.c_str(), "1"},
        {networkName.c_str(), ""},
        {networkSignal.c_str(), ""},
        {networkIP.c_str(), ""},
        {networkMode.c_str(), ""},
        {freeHeap.c_str(), ""},
        {"Back", "STATUS_BACK"},
    };

    showMenu(STATUS_MENU, SIZEOFARRAY(STATUS_MENU));
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
    String active = menuList->getActiveIdentifier();

    Serial.print(active);
    Serial.println(" clicked");

    if(active.equals("STATUS")) {
        showStatusMenu();
    }
    else if(active.equals("RESET")) {
        showMenu(RESET_MENU, SIZEOFARRAY(RESET_MENU));
    }
    else if(active.equals("RESET_TICKERS")) {
        manager->tickers->reset();
        ESP.restart();
    }
    else if(active.equals("RESET_SETTINGS")) {
        manager->settings->reset();
        ESP.restart();
    }
    else if(active.equals("RESET_FACTORY")) {
        manager->tickers->reset();
        manager->settings->reset();
        ESP.restart();
    }
    else if(active.equals("RESET_BACK")) {
        showMenu(MAIN_MENU, SIZEOFARRAY(MAIN_MENU));
    }
    else if(active.equals("STATUS_BACK")) {
        showMenu(MAIN_MENU, SIZEOFARRAY(MAIN_MENU));
    }
    else if(active.equals("BACK")) {
        manager->show(LAYOUT_TICKER);
    }
};