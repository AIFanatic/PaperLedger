#include "CoinGecko.h"

CoinGecko::CoinGecko(Manager *_manager) : DataSource(_manager) {
    ticker_url = "https://api.coingecko.com/api/v3/simple/price?include_24hr_vol=true&include_24hr_change=true&include_last_updated_at=true&include_24hr_vol=true&ids=%s&vs_currencies=%s";
    available_coins_url = "https://api.coingecko.com/api/v3/coins/list";
    available_currencies_url = "https://api.coingecko.com/api/v3/simple/supported_vs_currencies";
};

bool CoinGecko::supports(int provider) {
    return provider == COIN_GECKO;
}

TickerDataResult *CoinGecko::tickerData(JsonObject &ticker) {
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

    coin.toLowerCase();
    currency.toLowerCase();

    String price = responseJson[coin][currency];
    String last_update = responseJson[coin]["last_updated_at"];
    String vol_24h = "$ " + Utils::numToHuman(responseJson[coin][currency + "_24h_vol"], 2);
    String change_24h = String(Utils::roundDecimals(responseJson[coin][currency + "_24h_change"], 2));

    return new TickerDataResult(price, vol_24h, change_24h, last_update);
}