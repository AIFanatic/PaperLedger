#include "LayoutTicker.h"

LayoutTicker::LayoutTicker(Display *_display): LayoutBase(_display) {
    display->render->drawFromJson(reinterpret_cast<const char*>(MENU_MAIN));
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
    display->show(LAYOUT_SETUP);
};