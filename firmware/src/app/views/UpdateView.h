#ifndef UpdateView_H
#define UpdateView_H

#include "../helpers/LayoutBase.h"

class UpdateView: public LayoutBase {
    public:
        UpdateView(Manager *_manager);
        ~UpdateView(void);

        void update();

        void setText(const char *title, const char *message, const char *subMessage);

    private:
        void leftButtonClicked();
        void rightButtonClicked();
        void okButtonClicked();


};

#endif