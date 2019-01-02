#include "LayoutSetup.h"

LayoutSetup::LayoutSetup(Manager *_manager): LayoutBase(_manager) {
    initMenu();
    showMenu(MAIN_MENU, SIZEOFARRAY(MAIN_MENU));
};

LayoutSetup::~LayoutSetup() {
};

void LayoutSetup::initMenu() {
    // Init list
    menuList = new LayoutList(manager->render);
    menuList->init(0, 0, 296, 125, 12, BLACK);
}

void LayoutSetup::showMenu(const char *menu[][2], int size) {
    menuList->removeAll();
    menuList->addFromArray(menu, size);

    menuList->setActive(0);
}

void LayoutSetup::leftButtonClicked() {
    Serial.println("left button clicked");

    menuList->moveUp();
};

void LayoutSetup::rightButtonClicked() {
    Serial.println("right button clicked");

    menuList->moveDown();
};

void LayoutSetup::okButtonClicked() {
    const char *active = menuList->getActiveIdentifier();

    Serial.print(active);
    Serial.println(" clicked");

    if(strcmp(active, "TICKERS") == 0) {
        showMenu(TICKERS_MENU, SIZEOFARRAY(TICKERS_MENU));
    }
    else if(strcmp(active, "ADD_TICKER") == 0) {
        getTickers();
    }
    else if(strcmp(active, "BACK_TICKER") == 0) {
        showMenu(MAIN_MENU, SIZEOFARRAY(MAIN_MENU));
    }
    else if(strcmp(active, "RESET") == 0) {
        Serial.print("I should reset!!");
        manager->reset();
    }
    else if(strcmp(active, "BACK") == 0) {
        manager->show(LAYOUT_TICKER);
    }
    else if(strcmp(active, "COIN_MORE") == 0) {
        tickersCurrentPage++;
        getTickers();
    }
};

void LayoutSetup::getTickers() {
    HTTPClient http;
    String url = "https://api.coingecko.com/api/v3/coins/markets?vs_currency=usd&per_page=5&page=";
    url.concat(tickersCurrentPage);

    http.begin(url); //Specify the URL
    int httpCode = http.GET();

    if (httpCode > 0) { //Check for the returning code
        String payload = http.getString();

        DynamicJsonBuffer jsonBuffer;
        JsonArray& tickers = jsonBuffer.parseArray(payload);

        const char *coinsList[tickers.size() + 1][2];

        for(int i = 0; i < tickers.size(); i++) {
            String params = tickers[i];
            JsonObject& obj = jsonBuffer.parseObject( params );

            coinsList[i][0] = obj["name"];
            coinsList[i][1] = "COIN";
        }

        coinsList[tickers.size()][0] = "More";
        coinsList[tickers.size()][1] = "COIN_MORE";

        showMenu(coinsList, SIZEOFARRAY(coinsList));
    }
    else {
        Serial.println("Error on HTTP request");
    }
};