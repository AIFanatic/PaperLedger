#include "Manager.h"
#include "./views/MainView.h"
#include "./views/TickerView.h"
#include "./views/SetupView.h"
#include "./views/DisconnectedView.h"

Manager::Manager() {
    render = new Render();
    filesystem = new FileSystem();
    webserver = new WebServer(this);
    settings = new Settings(this);
    tickers = new Tickers(this);
    alarms = new Alarms(this);

    speaker = new SPEAKER();
    speaker->begin(SPEAKER_PIN_PIN, 0);

    render->clearScreen();

    webserver->needNetworkReconnect = true;
};

Manager::~Manager() {
};

// TODO: Ugly, fix
void Manager::show(int index) {
    isInitializingLayout = true;

    // if(currentLayout) {
    //     currentLayout = nullptr;
    // }

    if(index == VIEW_MAIN) {
        currentLayout = new MainView(this);
    }
    else if(index == TICKER_VIEW) {
        currentLayout = new TickerView(this);
    }
    else if(index == SETUP_VIEW) {
        currentLayout = new SetupView(this);
    }
    else if(index == DISCONNECTED_VIEW) {
        currentLayout = new DisconnectedView(this, currentIndex);
    }

    currentIndex = index;

    isInitializingLayout = false;
};

// TODO: Ugly, fix
void Manager::update() {
    if(!isInitializingLayout) {
        if(currentIndex == VIEW_MAIN) {
            (reinterpret_cast<MainView *>(currentLayout))->update();
        }
        else if(currentIndex == TICKER_VIEW) {
            (reinterpret_cast<TickerView *>(currentLayout))->update();
        }
        else if(currentIndex == SETUP_VIEW) {
            (reinterpret_cast<SetupView *>(currentLayout))->update();
        }
        else if(currentIndex == DISCONNECTED_VIEW) {
            (reinterpret_cast<DisconnectedView *>(currentLayout))->update();
        }
    }

    webserver->update();

    if(!webserver->hasInternetAccess && currentIndex != DISCONNECTED_VIEW && currentIndex != SETUP_VIEW) {
        show(DISCONNECTED_VIEW);
    }

    speaker->update();
}