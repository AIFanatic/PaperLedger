#include "Manager.h"
#include "./views/MainView.h"
#include "./views/TickerView.h"
#include "./views/SetupView.h"
#include "./views/DisconnectedView.h"
#include "./views/LoadingView.h"
#include "./views/UpdateView.h"

Manager::Manager() {
    render = new Render();
    filesystem = new FileSystem();
    webserver = new WebServer(this);
    settings = new Settings(this);
    tickers = new Tickers(this);
    alarms = new Alarms(this);
    updater = new Updater(this);

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

    // if(currentView) {
    //     currentView = nullptr;
    // }

    if(index == MAIN_VIEW) {
        currentView = new MainView(this);
    }
    else if(index == TICKER_VIEW) {
        currentView = new TickerView(this);
    }
    else if(index == SETUP_VIEW) {
        currentView = new SetupView(this);
    }
    else if(index == DISCONNECTED_VIEW) {
        currentView = new DisconnectedView(this);
    }
    else if(index == LOADING_VIEW) {
        currentView = new LoadingView(this);
    }
    else if(index == UPDATE_VIEW) {
        currentView = new UpdateView(this);
    }

    currentIndex = index;

    isInitializingLayout = false;
};

// TODO: Ugly, fix
void Manager::update() {
    if(!isInitializingLayout) {
        if(currentIndex == MAIN_VIEW) {
            (reinterpret_cast<MainView *>(currentView))->update();
        }
        else if(currentIndex == TICKER_VIEW) {
            (reinterpret_cast<TickerView *>(currentView))->update();
        }
        else if(currentIndex == SETUP_VIEW) {
            (reinterpret_cast<SetupView *>(currentView))->update();
        }
        else if(currentIndex == DISCONNECTED_VIEW) {
            (reinterpret_cast<DisconnectedView *>(currentView))->update();
        }
        else if(currentIndex == LOADING_VIEW) {
            (reinterpret_cast<LoadingView *>(currentView))->update();
        }
        else if(currentIndex == UPDATE_VIEW) {
            (reinterpret_cast<UpdateView *>(currentView))->update();
        }
    }

    webserver->update();

    if(!webserver->hasInternetAccess && currentIndex != DISCONNECTED_VIEW && currentIndex != SETUP_VIEW) {
        show(DISCONNECTED_VIEW);
    }

    speaker->update();
}

int Manager::getCurrentIndex() {
    return currentIndex;
}

void *Manager::getCurrentView() {
    return currentView;
}