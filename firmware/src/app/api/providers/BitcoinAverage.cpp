#include "BitcoinAverage.h"

#include "../../Manager.h"

BitcoinAverage::BitcoinAverage(Manager *_manager) : DataSource(_manager) {
    ticker_url = "https://apiv2.bitcoinaverage.com/indices/global/ticker/%s%s";
};

bool BitcoinAverage::supports(int provider) {
    return provider == BITCOIN_AVERAGE;
}

TickerDataResult *BitcoinAverage::tickerData(JsonObject &ticker) {
    String coin = ticker["coin"].as<String>();
    String currency = ticker["currency"].as<String>();

    char fullUrl[255];
    sprintf(fullUrl, ticker_url.c_str(), coin.c_str(), currency.c_str());

    String response = manager->webserver->get(fullUrl);
    if (response.length() == 0) {
        Serial.println("Failed to update tickers, invalid response");
        return NULL;
    }

    DynamicJsonBuffer responseJsonBuffer;
    JsonObject &responseJson = responseJsonBuffer.parse(response);

    String price = String(Utils::roundDecimals(responseJson["last"], 2));
    String volume = String(Utils::roundDecimals(responseJson["volume"], 2)) + " BTC";
    String changes = responseJson["changes"]["percent"]["day"].as<String>();
    String timestamp = responseJson["timestamp"].as<String>();

    return new TickerDataResult(price, volume, changes, timestamp);
}