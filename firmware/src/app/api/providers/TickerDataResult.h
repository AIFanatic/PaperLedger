#ifndef TickerDataResult_H
#define TickerDataResult_H

#include "Arduino.h"

class TickerDataResult {
    public:
        TickerDataResult(String _price, String _volume, String _change, String _lastUpdatedAt);

        String getPrice();
        String getVolume();
        String getChange();
        String getLastUpdatedAt();
};

#endif