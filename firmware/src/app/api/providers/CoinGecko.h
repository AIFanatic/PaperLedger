#ifndef CoinGecko_H
#define CoinGecko_H

#include "DataSource.h"
#include "../../Manager.h"

class CoinGecko : public DataSource {
    public:
        CoinGecko(Manager *_manager);

    private:
        String ticker_url;
        String available_coins_url;
        String available_currencies_url;

        TickerDataResult *tickerData(JsonObject &ticker);
        JsonArray &availableCoins();
        bool supports(int provider);
};

#endif