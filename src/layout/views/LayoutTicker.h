#ifndef LayoutTicker_H
#define LayoutTicker_H

#include "../Render.h"
#include "../Manager.h"
#include "../helpers/LayoutBase.h"

class LayoutTicker: public LayoutBase {
    public:
        LayoutTicker(Manager *_manager);
        ~LayoutTicker(void);

        void update();

    private:
        void leftButtonClicked();
        void rightButtonClicked();
        void okButtonClicked();

        void showTicker();
        void showNoTickers();

        int currentTicker = 0;

        long lastScreenUpdate = 0;
        long lastTickersUpdate = 0;

        int updateFrequency = 0;
        int scrollFrequency = 0;
};

#endif