#include "Manager.h"
#include "./views/MainView.h"
#include "./views/TickerView.h"
#include "./views/SetupView.h"
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
    battery = new Battery(this);

    speaker = new SPEAKER();
    speaker->begin(SPEAKER_PIN_PIN, 0);

    // Setup pins
    pinMode(RED_LED_PIN, OUTPUT);
    pinMode(VBAT_PIN, INPUT);
    pinMode(CHARGE_PIN, INPUT);

    webserver->needNetworkReconnect = true;

    loadView();
};

Manager::~Manager() {
};

void Manager::loadView() {
    // If device is not awaken by deep sleep load main view
    if(!Utils::hasBootedFromDeepSleep()) {
        render->clearScreen(false);
        setCurrentViewIndex(MAIN_VIEW);
    }

    show(getCurrentViewIndex());
}

// TODO: Ugly, fix
void Manager::show(int index) {
    isInitializingLayout = true;

    if(index == MAIN_VIEW) {
        currentView = new MainView(this);
    }
    else if(index == TICKER_VIEW) {
        currentView = new TickerView(this);
    }
    else if(index == SETUP_VIEW) {
        currentView = new SetupView(this);
    }
    else if(index == LOADING_VIEW) {
        currentView = new LoadingView(this);
    }
    else if(index == UPDATE_VIEW) {
        currentView = new UpdateView(this);
    }

    setCurrentViewIndex(index);

    isInitializingLayout = false;
};

// TODO: Ugly, fix
void Manager::update() {
    int currentViewIndex = getCurrentViewIndex();

    if(!isInitializingLayout) {
        if(currentViewIndex == MAIN_VIEW) {
            (static_cast<MainView *>(currentView))->update();
        }
        else if(currentViewIndex == TICKER_VIEW) {
            (static_cast<TickerView *>(currentView))->update();
        }
        else if(currentViewIndex == SETUP_VIEW) {
            (static_cast<SetupView *>(currentView))->update();
        }
        else if(currentViewIndex == LOADING_VIEW) {
            (static_cast<LoadingView *>(currentView))->update();
        }
        else if(currentViewIndex == UPDATE_VIEW) {
            (static_cast<UpdateView *>(currentView))->update();
        }
    }

    webserver->update();
    speaker->update();
    battery->update();
}

void *Manager::getCurrentView() {
    return currentView;
}

void Manager::enterDeepSleep() {
    esp_sleep_enable_ext0_wakeup(LEFT_BUTTON, LOW);
    esp_sleep_enable_ext0_wakeup(OK_BUTTON, LOW);
    esp_sleep_enable_ext0_wakeup(RIGHT_BUTTON, LOW);

    esp_deep_sleep_start();
}