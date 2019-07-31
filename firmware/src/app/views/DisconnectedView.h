#ifndef DisconnectedView_H
#define DisconnectedView_H

#include "../helpers/LayoutBase.h"

class DisconnectedView: public LayoutBase {
    public:
        DisconnectedView(Manager *_manager);
        ~DisconnectedView(void);

        void update();

    private:
        void leftButtonClicked();
        void rightButtonClicked();
        void okButtonClicked();
};

#endif