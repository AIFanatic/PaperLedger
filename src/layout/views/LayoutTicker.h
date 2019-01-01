#ifndef LayoutTicker_H
#define LayoutTicker_H

#include "../Render.h"
#include "../Manager.h"
#include "../helpers/LayoutBase.h"

class LayoutTicker: public LayoutBase {
    public:
        LayoutTicker(Manager *_manager);
        ~LayoutTicker(void);

    private:
        void leftButtonClicked();
        void rightButtonClicked();
        void okButtonClicked();
};

#endif