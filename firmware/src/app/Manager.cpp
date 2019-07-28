#include "Manager.h"
#include "./views/MainView.h"
#include "./views/TickerView.h"
#include "./views/SetupView.h"
#include "./views/DisconnectedView.h"
#include "./views/LoadingView.h"
#include "./views/UpdateView.h"
#include "./views/BatteryView.h"

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

    render->clearScreen();

    webserver->needNetworkReconnect = true;
};

Manager::~Manager() {
};

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
    else if(index == DISCONNECTED_VIEW) {
        currentView = new DisconnectedView(this);
    }
    else if(index == LOADING_VIEW) {
        currentView = new LoadingView(this);
    }
    else if(index == UPDATE_VIEW) {
        currentView = new UpdateView(this);
    }
    else if(index == BATTERY_VIEW) {
        currentView = new BatteryView(this);
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
        else if(currentIndex == BATTERY_VIEW) {
            (reinterpret_cast<BatteryView *>(currentView))->update();
        }
    }

    webserver->update();
    speaker->update();
    battery->update();

    if(currentIndex != SETUP_VIEW) {
        // Ordered by "warning" priority
        if(!battery->isCharging && battery->chargePercentage <= BATTERY_WARNING_PERCENTAGE && currentIndex != BATTERY_VIEW) {
            show(BATTERY_VIEW);
            return;
        }

        if(!webserver->hasInternetAccess && currentIndex != DISCONNECTED_VIEW) {
            show(DISCONNECTED_VIEW);
            return;
        }
    }
}

int Manager::getCurrentIndex() {
    return currentIndex;
}

void *Manager::getCurrentView() {
    return currentView;
}