#include "LayoutBase.h"

LayoutBase::LayoutBase(Manager *_manager) {
    manager = _manager;
    initButtons();

    statusView = new StatusView(_manager);
};

void LayoutBase::initButtons() {
    leftButton = new Pushbutton(LEFT_BUTTON);
    rightButton = new Pushbutton(RIGHT_BUTTON);
    okButton = new Pushbutton(OK_BUTTON);
};

void LayoutBase::updateButtons() {
    if (leftButton->getSingleDebouncedPress()) {
        beepIfNotMuted();
        leftButtonClicked();
    }

    if (rightButton->getSingleDebouncedPress()) {
        beepIfNotMuted();
        rightButtonClicked();
    }

    if (okButton->getSingleDebouncedPress()) {
        beepIfNotMuted();
        okButtonClicked();
    }
}

void LayoutBase::update() {
    updateButtons();
    statusView->update();
}

void LayoutBase::draw() {
    statusView->draw();
    manager->render->draw();
}

void LayoutBase::beepIfNotMuted() {
    if(manager->settings->get("mute_speakers") == "true") {
        return;
    }

    manager->speaker->tone(2240);
    delay(100);
    manager->speaker->mute();
}