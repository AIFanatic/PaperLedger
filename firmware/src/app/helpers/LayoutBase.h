#ifndef LAYOUTBASE_H
#define LAYOUTBASE_H

#include "../Manager.h"

#include <Pushbutton.h>

#include "./StatusView.h"

class LayoutBase {
    public:
        LayoutBase(Manager *_manager);
        virtual ~LayoutBase() = default;

        void update();

        virtual void leftButtonClicked() = 0;
        virtual void rightButtonClicked() = 0;
        virtual void okButtonClicked() = 0;

        Manager *manager;
        StatusView *statusView;

    private:
        void initButtons();
        void updateButtons();
        void beepIfNotMuted();

        Pushbutton *leftButton;
        Pushbutton *rightButton;
        Pushbutton *okButton;
};

#endif