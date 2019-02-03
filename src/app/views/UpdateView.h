#ifndef UpdateView_H
#define UpdateView_H

#include "../controller/Render.h"
#include "../Manager.h"
#include "../helpers/LayoutBase.h"

class UpdateView: public LayoutBase {
    public:
        UpdateView(Manager *_manager);
        ~UpdateView(void);

        void update();

    private:
        void leftButtonClicked();
        void rightButtonClicked();
        void okButtonClicked();
};

#endif