#ifndef LayoutDisconnected_H
#define LayoutDisconnected_H

#include "../Render.h"
#include "../Manager.h"
#include "../helpers/LayoutBase.h"

class LayoutDisconnected: public LayoutBase {
    public:
        LayoutDisconnected(Manager *_manager);
        ~LayoutDisconnected(void);

        void update();

    private:
        void leftButtonClicked();
        void rightButtonClicked();
        void okButtonClicked();
};

#endif