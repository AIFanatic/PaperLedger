#include "Manager.h"
#include "./views/LayoutTicker.h"
#include "./views/LayoutSetup.h"

Manager::Manager() {
    render = new Render();
    filesystem = new FileSystem();
    networkManager = new NetworkManager(this);
    settings = new Settings(this);

    render->clearScreen();

    networkManager->needNetworkReconnect = true;
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

    networkManager->update();
}

void Manager::reset() {
    settings->reset();
}