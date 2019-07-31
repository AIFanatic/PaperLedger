#ifndef BatteryView_H
#define BatteryView_H

#include "../helpers/LayoutBase.h"

class BatteryView: public LayoutBase {
    public:
        BatteryView(Manager *_manager);
        ~BatteryView(void);

        void update();

    private:
        void leftButtonClicked();
        void rightButtonClicked();
        void okButtonClicked();
};

#endif