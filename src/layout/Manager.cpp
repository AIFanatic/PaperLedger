#include "Manager.h"
#include "./views/LayoutTicker.h"
#include "./views/LayoutSetup.h"

Manager::Manager() {
    utils = new Utils();
    render = new Render();
    filesystem = new FileSystem();
    requestManager = new RequestManager(this);
    settings = new Settings(this);

    render->clearScreen();

    needNetworkReconnect = true;
};

Manager::~Manager() {
};

// TODO: Ugly, fix
void Manager::show(int index) {
    isInitializingLayout = true;

    if(currentLayout) {
        currentLayout = nullptr;
    }

    if(index == LAYOUT_TICKER) {
        currentLayout = new LayoutTicker(this);
    }
    else if(index == LAYOUT_SETUP) {
        currentLayout = new LayoutSetup(this);
    }

    currentIndex = index;

    isInitializingLayout = false;
};

// TODO: Ugly, fix
void Manager::update() {
    if(!isInitializingLayout) {
        if(currentIndex == LAYOUT_TICKER) {
            (reinterpret_cast<LayoutTicker *>(currentLayout))->update();
        }
        else if(currentIndex == LAYOUT_SETUP) {
            (reinterpret_cast<LayoutSetup *>(currentLayout))->update();
        }
    }

    // Its better to handle network reconnects in a loop instead of a request
    if(needNetworkReconnect) {
        requestManager->reset();
        utils->disconnectWifi();
        connectNetwork();
        requestManager->begin();

        needNetworkReconnect = false;
    }
}

void Manager::connectNetwork() {
    String ssid = settings->get("ssid");
    String password = settings->get("password");

    Serial.println(ssid);
    Serial.println(password);
    
    if(!utils->connectWifi(ssid.c_str(), password.c_str())) {
        Serial.println("Unable to connect to wifi, creating AP");
        if(!utils->connectAP("inkCrypto")) {
            Serial.println("Unable to connect to Wifi or to create Access Point");
            esp_restart();
        }
    }
}

void Manager::reset() {
    settings->reset();
}