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

        long lastScreenUpdate = 0;

        // TODO: Should be in settings
        long lastTickersUpdate = 0;

        int currentTicker = 0;
};

#endif