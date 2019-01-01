#include "LayoutTicker.h"

LayoutTicker::LayoutTicker(Manager *_manager): LayoutBase(_manager) {
    manager->render->drawFromJson(reinterpret_cast<const char*>(MENU_MAIN));
};

LayoutTicker::~LayoutTicker() {
};

void LayoutTicker::leftButtonClicked() {
    Serial.println("MAIN - left button clicked");
};

void LayoutTicker::rightButtonClicked() {
    Serial.println("right button clicked");
};

void LayoutTicker::okButtonClicked() {
    Serial.println("ok button clicked");
    manager->show(LAYOUT_SETUP);
};