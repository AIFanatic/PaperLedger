#ifndef LAYOUTBASE_H
#define LAYOUTBASE_H

#include "../Render.h"
#include "../Display.h"

#include <Pushbutton.h>

class LayoutBase {
    public:

        LayoutBase(Display *_display);
        // virtual ~LayoutBase() {};

        void update();

        Display *display;

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