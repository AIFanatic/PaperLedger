#include "LayoutBase.h"

void LayoutBase::initButtons() {
    Serial.println("BUTTONS INIT");

    leftButton = new Pushbutton(LEFT_BUTTON);
    rightButton = new Pushbutton(RIGHT_BUTTON);
    okButton = new Pushbutton(OK_BUTTON);
};

void LayoutBase::updateButtons() {
    if (leftButton->getSingleDebouncedPress()) {
        leftButtonClicked();
    }
    if (rightButton->getSingleDebouncedPress()) {
        rightButtonClicked();
    }
    if (okButton->getSingleDebouncedPress()) {
        okButtonClicked();
    }
}

void LayoutBase::update() {
    updateButtons();
}