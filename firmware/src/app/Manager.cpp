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

    webserver->needNetworkReconnect = true;

    loadView();
};

Manager::~Manager() {
};

void Manager::loadView() {
    // If device is not awaken by deep sleep load main view
    if(!Utils::hasBootedFromDeepSleep()) {
        render->clearScreen(false);
        RTC::write(RTC_STORAGE::CURRENT_VIEW_INDEX, LOADING_VIEW);
    }

    currentViewIndex = RTC::read(RTC_STORAGE::CURRENT_VIEW_INDEX);
    show(currentViewIndex);
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

    currentViewIndex = index;
    RTC::write(RTC_STORAGE::CURRENT_VIEW_INDEX, currentViewIndex);

    isInitializingLayout = false;
};

// TODO: Ugly, fix
void Manager::update() {
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
        else if(currentViewIndex == DISCONNECTED_VIEW) {
            (static_cast<DisconnectedView *>(currentView))->update();
        }
        else if(currentViewIndex == LOADING_VIEW) {
            (static_cast<LoadingView *>(currentView))->update();
        }
        else if(currentViewIndex == UPDATE_VIEW) {
            (static_cast<UpdateView *>(currentView))->update();
        }
        else if(currentViewIndex == BATTERY_VIEW) {
            (static_cast<BatteryView *>(currentView))->update();
        }
    }

    webserver->update();
    speaker->update();
    battery->update();

    if(currentViewIndex != SETUP_VIEW) {
        // Ordered by "warning" priority
        if(!battery->isCharging && battery->chargePercentage <= BATTERY_WARNING_PERCENTAGE && currentViewIndex != BATTERY_VIEW) {
            show(BATTERY_VIEW);
            return;
        }

        if(!webserver->hasInternetAccess && currentViewIndex != DISCONNECTED_VIEW) {
            show(DISCONNECTED_VIEW);
            return;
        }
    }
}

void *Manager::getCurrentView() {
    return currentView;
}