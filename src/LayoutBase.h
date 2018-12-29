#ifndef LAYOUTBASE_H
#define LAYOUTBASE_H

#include <Render.h>
#include <Pushbutton.h>

#include "menus.h"

class LayoutBase {
    public:

        LayoutBase(Render*) ;
        LayoutBase(const LayoutBase& base) ;
        LayoutBase& operator=(const LayoutBase& base) = default;
        virtual ~LayoutBase() {};

        void update();

    private:
        void initButtons();
        void updateButtons();

        void leftButtonClicked();
        void rightButtonClicked();
        void okButtonClicked();

        Render *render;

        Pushbutton *leftButton;
        Pushbutton *rightButton;
        Pushbutton *okButton;
};

#endif