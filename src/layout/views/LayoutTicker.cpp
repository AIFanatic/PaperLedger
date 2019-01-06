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
    Serial.println("MAIN - left button clicked");
};

void LayoutTicker::rightButtonClicked() {
    Serial.println("right button clicked");
};

void LayoutTicker::okButtonClicked() {
    Serial.println("ok button clicked");
    manager->show(LAYOUT_SETUP);
};

void LayoutTicker::showTicker() {
    JsonArray& tickers = manager->tickers->get();

    if(currentTicker > tickers.size() - 1) {
        currentTicker = 0;
    }

    String tickerStr = tickers[currentTicker];

    DynamicJsonBuffer jsonBuffer;
    JsonObject& ticker = jsonBuffer.parse(tickerStr);

    String coin = ticker["coin"];
    String price = ticker["price"];
    String currency = ticker["currency"];

    String pricePretty = price + " " + currency;

    manager->render->fillScreen(1);
    manager->render->drawRectangle(0, 0, 296, 50, BLACK, 1);
    manager->render->drawText(0, 35, coin.c_str(), 18, WHITE, CENTER_ALIGNMENT);
    manager->render->drawText(0, 100, pricePretty.c_str(), 18, BLACK, CENTER_ALIGNMENT);
    manager->render->draw();
}

void LayoutTicker::update() {
    LayoutBase::update();

    unsigned long currentTime = millis();

    if((currentTime - lastScreenUpdate) / 1000 > scrollFrequency) {
        currentTicker++;
        lastScreenUpdate = currentTime;
        showTicker();
    }

    if((currentTime - lastTickersUpdate) / 1000 > updateFrequency) {
        manager->tickers->updatePrices();
        lastTickersUpdate = currentTime;
    }
}