#ifndef DataSource_H
#define DataSource_H

#include "../../Manager.h"
#include "TickerDataResult.h"

class DataSource {
    public:
        Manager *manager;
        DataSource(Manager *_manager);

        virtual TickerDataResult *tickerData(JsonObject &ticker) = 0;
        virtual bool supports(int provider) = 0;
};

#endif