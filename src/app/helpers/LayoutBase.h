#ifndef LAYOUTBASE_H
#define LAYOUTBASE_H

#include "../controller/Render.h"
#include "../Manager.h"

#include <Pushbutton.h>

class LayoutBase {
    public:

        LayoutBase(Manager *_manager);
        // virtual ~LayoutBase() {};

        void update();

        Manager *manager;

        virtual void leftButtonClicked() = 0;
        virtual void rightButtonClicked() = 0;
        virtual void okButtonClicked() = 0;

    private:
        void initButtons();
        void updateButtons();

        Pushbutton *leftButton;
        Pushbutton *rightButton;
        Pushbutton *okButton;
};

#endif