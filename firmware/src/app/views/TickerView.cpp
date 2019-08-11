#include "TickerView.h"

TickerView::TickerView(Manager *_manager): LayoutBase(_manager) {
    updateFrequency = manager->settings->get("tickers_update_frequency").toInt();
    scrollFrequency = manager->settings->get("tickers_scroll_frequency").toInt();

    if(!manager->deepSleep->hasBootedFromDeepSleep()) {
        long currentTime = Utils::getCurrentTime();
        setLastScrollUpdate(currentTime);
        setLastTickersUpdate(currentTime);
    }

    if(manager->deepSleep->getWakeupCause() == ESP_SLEEP_WAKEUP_EXT0) {
        manager->deepSleep->setMinAwakeBootTimeOffset(MIN_AWAKE_TIME_MS);
        if(!manager->webserver->hasInternetAccess) {
            manager->webserver->needNetworkReconnect = true;
        }
    }

    showTicker();
};

TickerView::~TickerView() {
};

void TickerView::leftButtonClicked() {
    manager->deepSleep->setMinAwakeBootTimeOffset(MIN_AWAKE_TIME_MS);
    gotoPreviousTicker();
};

void TickerView::rightButtonClicked() {
    manager->deepSleep->setMinAwakeBootTimeOffset(MIN_AWAKE_TIME_MS);
    gotoNextTicker();
};

void TickerView::okButtonClicked() {
    manager->show(MAIN_VIEW);
};

void TickerView::gotoPreviousTicker() {
    setCurrentTickerIndex(getCurrentTickerIndex() - 1);
    setLastScrollUpdate(Utils::getCurrentTime());
    showTicker();
}

void TickerView::gotoNextTicker() {
    setCurrentTickerIndex(getCurrentTickerIndex() + 1);
    setLastScrollUpdate(Utils::getCurrentTime());
    showTicker();
}

void TickerView::showNoTickers() {
    manager->render->fillScreen(1);
    manager->render->drawRectangle(0, 0, 296, 50, BLACK, 1);
    manager->render->drawText(0, 35, "No tickers", 18, WHITE, CENTER_ALIGNMENT);
    manager->render->drawText(0, 85, "Manage your tickers in the", 9, BLACK, CENTER_ALIGNMENT);
    manager->render->drawText(0, 110, "Web Portal" , 9, BLACK, CENTER_ALIGNMENT);
    manager->render->draw();
}

// TODO: Show ticker by index. RTC is uint, no negative numbers
void TickerView::showTicker() {
    String str = manager->tickers->get();
    DynamicJsonBuffer buffer;
    JsonArray& tickers = buffer.parse(str);

    if(tickers.size() == 0) {
        showNoTickers();
        return;
    }

    int tickersSize = tickers.size() - 1;

    if(getCurrentTickerIndex() > tickersSize) {
        setCurrentTickerIndex(0);
    }

    if(getCurrentTickerIndex() < 0) {
        setCurrentTickerIndex(tickersSize);
    }

    JsonObject& ticker = tickers[getCurrentTickerIndex()].as<JsonObject>();

    String coin = ticker["coin"];
    String price = ticker["price"];
    String currency = ticker["currency"];

    String pricePretty = price + " " + currency;

    String vol_24h = ticker["vol_24h"];
    String change_24h = ticker["change_24h"];
    String stats = "24h: " + change_24h + " " + (char)37 + " | Vol: $" + vol_24h; // % character needs to be passed directly

    String last_update = "Never";
    if(ticker["last_update"] != "0") {
        last_update = Utils::readableTimestamp(ticker["last_update"], manager->settings->get("utc_offset").toInt());
    }

    Serial.printf("Last update: %s %lu\n", last_update.c_str(), manager->settings->get("utc_offset").toInt());

    manager->render->fillScreen(1);
    manager->render->drawText(0, 45, coin.c_str(), 18, BLACK, CENTER_ALIGNMENT);
    manager->render->drawText(0, 82, pricePretty.c_str(), 18, BLACK, CENTER_ALIGNMENT);
    manager->render->drawText(0, 105, stats.c_str(), 8, BLACK, CENTER_ALIGNMENT);
    manager->render->drawText(0, 122, last_update.c_str(), 7, BLACK, CENTER_ALIGNMENT);
    
    statusView->draw();
    manager->render->draw();
}

void TickerView::update() {
    LayoutBase::update();

    statusView->update();

    long currentTime = Utils::getCurrentTime();

    if((currentTime - getLastTickersUpdate()) > updateFrequency) {
        if(!manager->webserver->hasInternetAccess) {
            manager->webserver->needNetworkReconnect = true;
            return;
        }
        manager->tickers->updateTickers();
        manager->alarms->checkAlarms();
        setLastTickersUpdate(currentTime);
        updateFrequency = manager->settings->get("tickers_update_frequency").toInt();
    }

    if((currentTime - getLastScrollUpdate()) > scrollFrequency) {
        gotoNextTicker();
        scrollFrequency = manager->settings->get("tickers_scroll_frequency").toInt();
    }

    // Enter deep sleep
    if(manager->deepSleep->canEnterDeepSleep()) {
        esp_sleep_enable_timer_wakeup(scrollFrequency * 1000); // uS
        manager->deepSleep->enterDeepSleep();
    }
}