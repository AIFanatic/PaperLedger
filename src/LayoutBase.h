#ifndef LAYOUTBASE_H
#define LAYOUTBASE_H

#include <Render.h>
#include <Pushbutton.h>

#include "menus.h"

class LayoutBase {
    public:

        LayoutBase(Render *_render, void *_display);
        // virtual ~LayoutBase() {};

        void update();

        Render *render;
        void *display;

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