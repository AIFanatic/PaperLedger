#include "LayoutBase.h"

LayoutBase::LayoutBase(Manager *_manager) {
    manager = _manager;
    initButtons();
};

void LayoutBase::initButtons() {
    leftButton = new Pushbutton(LEFT_BUTTON);
    rightButton = new Pushbutton(RIGHT_BUTTON);
    okButton = new Pushbutton(OK_BUTTON);
};

void LayoutBase::updateButtons() {
    if (leftButton->getSingleDebouncedPress()) {
        if(manager->settings->get("mute_speakers") != "true") {
            manager->speaker->tone(2240);
            delay(100);
            manager->speaker->mute();
        }
        
        leftButtonClicked();
    }

    if (rightButton->getSingleDebouncedPress()) {
        if(manager->settings->get("mute_speakers") != "true") {
            manager->speaker->tone(2240);
            delay(100);
            manager->speaker->mute();
        }
        
        rightButtonClicked();
    }

    if (okButton->getSingleDebouncedPress()) {
        if(manager->settings->get("mute_speakers") != "true") {
            manager->speaker->tone(2240);
            delay(100);
            manager->speaker->mute();
        }

        okButtonClicked();
    }
}

void LayoutBase::update() {
    updateButtons();
}