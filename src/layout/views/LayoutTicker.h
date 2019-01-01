#ifndef LayoutTicker_H
#define LayoutTicker_H

#include "../Render.h"
#include "../Display.h"
#include "../helpers/LayoutBase.h"

class LayoutTicker: public LayoutBase {
    public:
        LayoutTicker(Display *_display);
        ~LayoutTicker(void);

    private:
        void leftButtonClicked();
        void rightButtonClicked();
        void okButtonClicked();
};

#endif