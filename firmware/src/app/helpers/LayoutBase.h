#ifndef LAYOUTBASE_H
#define LAYOUTBASE_H

#include "../Manager.h"

#include <Pushbutton.h>

#include "./StatusView.h"

class LayoutBase {
    public:
        Manager *manager;
        LayoutBase(Manager *_manager);

        void update();
        void draw();

        virtual void leftButtonClicked() = 0;
        virtual void rightButtonClicked() = 0;
        virtual void okButtonClicked() = 0;

    private:
        void initButtons();
        void updateButtons();
        void beepIfNotMuted();

        Pushbutton *leftButton;
        Pushbutton *rightButton;
        Pushbutton *okButton;

        StatusView *statusView;
};

#endif