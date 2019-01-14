#include "LayoutTicker.h"

LayoutTicker::LayoutTicker(Manager *_manager): LayoutBase(_manager) {
    showTicker();

    // Init
    updateFrequency = manager->settings->get("tickers_update_frequency").toInt();
    scrollFrequency = manager->settings->get("tickers_scroll_frequency").toInt();

    lastScreenUpdate = millis();
    lastTickersUpdate = millis();
};

LayoutTicker::~LayoutTicker() {
};

void LayoutTicker::leftButtonClicked() {
    gotoPreviousTicker();
};

void LayoutTicker::rightButtonClicked() {
    gotoNextTicker();
};

void LayoutTicker::okButtonClicked() {
    manager->show(LAYOUT_SETUP);
};

void LayoutTicker::gotoPreviousTicker() {
    currentTicker--;
    lastScreenUpdate = millis();
    showTicker();
}

void LayoutTicker::gotoNextTicker() {
    currentTicker++;
    lastScreenUpdate = millis();
    showTicker();
}

void LayoutTicker::showNoTickers() {
    manager->render->fillScreen(1);
    manager->render->drawRectangle(0, 0, 296, 50, BLACK, 1);
    manager->render->drawText(0, 35, "No tickers", 18, WHITE, CENTER_ALIGNMENT);
    manager->render->drawText(0, 85, "Manage your tickers in the", 9, BLACK, CENTER_ALIGNMENT);
    manager->render->drawText(0, 110, "Web Portal" , 9, BLACK, CENTER_ALIGNMENT);
    manager->render->draw();
}

void LayoutTicker::showTicker() {
    JsonArray& tickers = manager->tickers->get();

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

    String tickerStr = tickers[currentTicker];

    DynamicJsonBuffer jsonBuffer;
    JsonObject& ticker = jsonBuffer.parse(tickerStr);

    String coin = ticker["coin"];
    String price = ticker["price"];
    String currency = ticker["currency"];

    String pricePretty = price + " " + currency;



    String last_update = ticker["last_update"];
    String change_24h = ticker["change_24h"];
    String vol_24h = ticker["vol_24h"];

    String status = "24h: " + change_24h + " | Vol: $" + vol_24h;



    manager->render->fillScreen(1);
    manager->render->drawRectangle(0, 0, 296, 70, BLACK, 1);
    manager->render->drawText(0, 15, status.c_str(), 9, WHITE, CENTER_ALIGNMENT);
    manager->render->drawText(0, 55, coin.c_str(), 18, WHITE, CENTER_ALIGNMENT);
    manager->render->drawText(0, 110, pricePretty.c_str(), 18, BLACK, CENTER_ALIGNMENT);
    manager->render->draw();
}

void LayoutTicker::update() {
    LayoutBase::update();

    unsigned long currentTime = millis();

    if((currentTime - lastScreenUpdate) / 1000 > scrollFrequency) {
        gotoNextTicker();
        scrollFrequency = manager->settings->get("tickers_scroll_frequency").toInt();
    }

    if((currentTime - lastTickersUpdate) / 1000 > updateFrequency) {
        manager->tickers->updateTickers();
        lastTickersUpdate = currentTime;
        updateFrequency = manager->settings->get("tickers_update_frequency").toInt();
    }
}