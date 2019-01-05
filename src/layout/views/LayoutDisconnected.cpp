#include "LayoutDisconnected.h"

LayoutDisconnected::LayoutDisconnected(Manager *_manager): LayoutBase(_manager) {
    // manager->render->drawFromJson(reinterpret_cast<const char*>(MENU_MAIN));

    manager->render->fillScreen(WHITE);
    manager->render->drawText(35, 40, "No Internet", 18, BLACK);

    String networkName = "Network name: ";
    String networkIP = "Network IP: ";

    networkName.concat(AP_NAME);
    networkIP.concat(AP_IP);

    manager->render->drawText(35, 40, "No Internet", 18, BLACK);
    manager->render->drawText(15, 75, networkName.c_str(), 9, BLACK);
    manager->render->drawText(15, 100, networkIP.c_str(), 9, BLACK);
    manager->render->draw();
};

LayoutDisconnected::~LayoutDisconnected() {
};

void LayoutDisconnected::leftButtonClicked() {
    Serial.println("MAIN - left button clicked");
};

void LayoutDisconnected::rightButtonClicked() {
    Serial.println("right button clicked");
};

void LayoutDisconnected::okButtonClicked() {
    Serial.println("ok button clicked");
    manager->show(LAYOUT_SETUP);
};

void LayoutDisconnected::update() {
    LayoutBase::update();
}