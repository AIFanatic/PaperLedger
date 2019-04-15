#ifndef BitcoinAverage_H
#define BitcoinAverage_H

#include "DataSource.h"

class BitcoinAverage : public DataSource {
    public:
        BitcoinAverage(Manager *_manager);

    private:
        String ticker_url;
        String available_coins_url;
        String available_currencies_url;

        TickerDataResult *tickerData(JsonObject &ticker);
        bool supports(int provider);
};

#endif