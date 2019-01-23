#include "Manager.h"
#include "./views/LayoutMain.h"
#include "./views/LayoutTicker.h"
#include "./views/LayoutSetup.h"
#include "./views/LayoutDisconnected.h"

Manager::Manager() {
    render = new Render();
    filesystem = new FileSystem();
    networkManager = new NetworkManager(this);
    settings = new Settings(this);
    tickers = new Tickers(this);

    speaker = new SPEAKER();
    speaker->begin(SPEAKER_PIN_PIN, 0);

    render->clearScreen();

    networkManager->needNetworkReconnect = true;
};

Manager::~Manager() {
};

// TODO: Ugly, fix
void Manager::show(int index) {
    isInitializingLayout = true;

    // if(currentLayout) {
    //     currentLayout = nullptr;
    // }

    if(index == LAYOUT_MAIN) {
        currentLayout = new LayoutMain(this);
    }
    else if(index == LAYOUT_TICKER) {
        currentLayout = new LayoutTicker(this);
    }
    else if(index == LAYOUT_SETUP) {
        currentLayout = new LayoutSetup(this);
    }
    else if(index == LAYOUT_DISCONNECTED) {
        currentLayout = new LayoutDisconnected(this, currentIndex);
    }

    currentIndex = index;

    isInitializingLayout = false;
};

// TODO: Ugly, fix
void Manager::update() {
    if(!isInitializingLayout) {
        if(currentIndex == LAYOUT_MAIN) {
            (reinterpret_cast<LayoutMain *>(currentLayout))->update();
        }
        else if(currentIndex == LAYOUT_TICKER) {
            (reinterpret_cast<LayoutTicker *>(currentLayout))->update();
        }
        else if(currentIndex == LAYOUT_SETUP) {
            (reinterpret_cast<LayoutSetup *>(currentLayout))->update();
        }
        else if(currentIndex == LAYOUT_DISCONNECTED) {
            (reinterpret_cast<LayoutDisconnected *>(currentLayout))->update();
        }
    }

    networkManager->update();

    if(!networkManager->hasInternetAccess && currentIndex != LAYOUT_DISCONNECTED && currentIndex != LAYOUT_SETUP) {
        show(LAYOUT_DISCONNECTED);
    }

    speaker->update();
}