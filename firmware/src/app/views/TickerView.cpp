#include "TickerView.h"

TickerView::TickerView(Manager *_manager): LayoutBase(_manager) {
    // Init
    updateFrequency = manager->settings->get("tickers_update_frequency").toInt();
    scrollFrequency = manager->settings->get("tickers_scroll_frequency").toInt();

    // TODO: ONLY IF NORMAL BOOT
    if(!Utils::hasBootedFromDeepSleep()) {
        long currentTime = Utils::getCurrentTime();
        setLastScrollUpdate(currentTime);
        setLastTickersUpdate(currentTime);
    }

    showTicker();
};

TickerView::~TickerView() {
};

void TickerView::leftButtonClicked() {
    gotoPreviousTicker();
};

void TickerView::rightButtonClicked() {
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
    String last_update = ticker["last_update"] != "0" ? Utils::readableTimestamp(ticker["last_update"]) : "Never";
    String status = "24h: " + change_24h + " " + (char)37 + " | Vol: $" + vol_24h; // % character needs to be passed directly

    manager->render->fillScreen(1);
    manager->render->drawText(0, 10, last_update.c_str(), 7, BLACK, RIGHT_ALIGNMENT);
    manager->render->drawText(0, 52, coin.c_str(), 18, BLACK, CENTER_ALIGNMENT);
    manager->render->drawText(0, 92, pricePretty.c_str(), 18, BLACK, CENTER_ALIGNMENT);
    manager->render->drawText(0, 117, status.c_str(), 8, BLACK, CENTER_ALIGNMENT);
    manager->render->draw();
}

void TickerView::update() {
    LayoutBase::update();

    long currentTime = Utils::getCurrentTime();

    if((currentTime - getLastScrollUpdate()) > (scrollFrequency * 1000)) {
        gotoNextTicker();
        scrollFrequency = manager->settings->get("tickers_scroll_frequency").toInt();
    }

    if((currentTime - getLastTickersUpdate()) > (updateFrequency * 1000) && manager->webserver->hasInternetAccess) {
        manager->tickers->updateTickers();
        manager->alarms->checkAlarms();
        setLastTickersUpdate(currentTime);
        updateFrequency = manager->settings->get("tickers_update_frequency").toInt();
    }
}

void TickerView::enterDeepSleep(uint64_t sleepTimeMillis) {
    esp_sleep_enable_ext0_wakeup(LEFT_BUTTON, LOW);
    esp_sleep_enable_ext0_wakeup(OK_BUTTON, LOW);
    esp_sleep_enable_ext0_wakeup(RIGHT_BUTTON, LOW);
    esp_sleep_enable_timer_wakeup(sleepTimeMillis * 1000); // uS

    esp_deep_sleep_start();
}