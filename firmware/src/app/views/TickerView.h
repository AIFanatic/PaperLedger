#ifndef TickerView_H
#define TickerView_H

#include "../controller/Render.h"
#include "../Manager.h"
#include "../helpers/LayoutBase.h"

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

        int currentTicker = 0;

        long lastScreenUpdate = 0;
        long lastTickersUpdate = 0;

        int updateFrequency = 0;
        int scrollFrequency = 0;
};

#endif