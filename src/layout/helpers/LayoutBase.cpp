#include "LayoutBase.h"

LayoutBase::LayoutBase(Manager *_manager) {
    manager = _manager;
    initButtons();
};

void LayoutBase::initButtons() {
    Serial.println("LayoutBase BUTTONS INIT");

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