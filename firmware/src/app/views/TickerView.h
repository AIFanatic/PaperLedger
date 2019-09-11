#ifndef TickerView_H
#define TickerView_H

#include "../helpers/LayoutBase.h"
#include "../helpers/Utils.h"

class TickerView: public LayoutBase {
    public:
        TickerView(Manager *_manager);
        ~TickerView(void);

        void update();

    private:
        void leftButtonClicked();
        void rightButtonClicked();
        void okButtonClicked();

        void gotoPreviousTicker();
        void gotoNextTicker();
        void showTicker();
        void showNoTickers();

        void enterDeepSleep(uint64_t sleepTimeMillis);

        void setCurrentTickerIndex(int value) { RTC::write(RTC_STORAGE::TICKER_INDEX, value); }
        int getCurrentTickerIndex() { return RTC::read(RTC_STORAGE::TICKER_INDEX); }

        void setLastTickersUpdate(long value) { RTC::writeLong(RTC_STORAGE::TICKER_LAST_TICKERS_UPDATE, value); }
        long getLastTickersUpdate() { return RTC::readLong(RTC_STORAGE::TICKER_LAST_TICKERS_UPDATE); }

        void setLastScrollUpdate(long value) { RTC::writeLong(RTC_STORAGE::TICKER_LAST_SCROLL_UPDATE, value); }
        long getLastScrollUpdate() { return RTC::readLong(RTC_STORAGE::TICKER_LAST_SCROLL_UPDATE); }

        int updateFrequency = 0;
        int scrollFrequency = 0;

        bool hasTickers = false;
};

#endif