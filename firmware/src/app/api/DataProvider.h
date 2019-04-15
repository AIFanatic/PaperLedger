#ifndef DataProvider_H
#define DataProvider_H

#include "../Manager.h"

#include "providers/DataSource.h"
#include "providers/BitcoinAverage.h"
#include "providers/CoinGecko.h"

class DataProvider {
    public:
        Manager *manager;

        DataProvider(Manager *_manager);
        DataSource *get();
};

#endif