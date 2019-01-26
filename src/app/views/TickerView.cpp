#include "TickerView.h"

TickerView::TickerView(Manager *_manager): LayoutBase(_manager) {
    showTicker();

    // Init
    updateFrequency = manager->settings->get("tickers_update_frequency").toInt();
    scrollFrequency = manager->settings->get("tickers_scroll_frequency").toInt();

    lastScreenUpdate = millis();
    lastTickersUpdate = millis();
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
    manager->show(VIEW_MAIN);
    manager->tickers->updateTickers();
};

void TickerView::gotoPreviousTicker() {
    currentTicker--;
    lastScreenUpdate = millis();
    showTicker();
}

void TickerView::gotoNextTicker() {
    currentTicker++;
    lastScreenUpdate = millis();
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

    if(currentTicker > tickersSize) {
        currentTicker = 0;
    }

    if(currentTicker < 0) {
        currentTicker = tickersSize;
    }

    JsonObject& ticker = tickers[currentTicker].as<JsonObject>();

    String coin = ticker["coin"];
    String price = ticker["price"];
    String currency = ticker["currency"];

    String pricePretty = price + " " + currency;

    String last_update = ticker["last_update"];
    String change_24h = ticker["change_24h"];
    String vol_24h = ticker["vol_24h"];
    String status = "24h: " + change_24h + " " + (char)37 + " | Vol: $" + vol_24h; // % character needs to be passed directly

    manager->render->fillScreen(1);
    manager->render->drawText(0, 35, coin.c_str(), 18, BLACK, CENTER_ALIGNMENT);
    manager->render->drawText(0, 80, pricePretty.c_str(), 18, BLACK, CENTER_ALIGNMENT);
    manager->render->drawText(0, 115, status.c_str(), 9, BLACK, CENTER_ALIGNMENT);
    manager->render->draw();
}

void TickerView::update() {
    LayoutBase::update();

    unsigned long currentTime = millis();

    if((currentTime - lastScreenUpdate) / 1000 > scrollFrequency) {
        gotoNextTicker();
        scrollFrequency = manager->settings->get("tickers_scroll_frequency").toInt();
    }

    if((currentTime - lastTickersUpdate) / 1000 > updateFrequency) {
        manager->tickers->updateTickers();
        manager->alarms->checkAlarms();
        lastTickersUpdate = currentTime;
        updateFrequency = manager->settings->get("tickers_update_frequency").toInt();
    }
}