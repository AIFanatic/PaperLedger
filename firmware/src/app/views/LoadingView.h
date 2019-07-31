#ifndef LoadingView_H
#define LoadingView_H

#include "../helpers/LayoutBase.h"

class LoadingView: public LayoutBase {
    public:
        LoadingView(Manager *_manager);
        ~LoadingView(void);

        void update();

    private:
        void leftButtonClicked();
        void rightButtonClicked();
        void okButtonClicked();
};

#endif