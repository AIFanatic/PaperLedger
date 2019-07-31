#include "DisconnectedView.h"

DisconnectedView::DisconnectedView(Manager *_manager): LayoutBase(_manager) {
    String networkName = "Network name: " + String(AP_NAME);
    String networkIP = "Web Portal: http://";

    String apNameLower = String(AP_NAME);
    apNameLower.toLowerCase();

    networkIP.concat(apNameLower + ".local");

    manager->render->fillScreen(WHITE);
    manager->render->drawRectangle(0, 0, 296, 50, BLACK, 1);
    manager->render->drawText(0, 35, "No Internet", 18, WHITE, CENTER_ALIGNMENT);
    manager->render->drawText(0, 85, networkName.c_str(), 9, BLACK, CENTER_ALIGNMENT);
    manager->render->drawText(0, 110, networkIP.c_str() , 9, BLACK, CENTER_ALIGNMENT);
    manager->render->draw();
};

DisconnectedView::~DisconnectedView() {
};

void DisconnectedView::leftButtonClicked() {
    Serial.println("MAIN - left button clicked");
};

void DisconnectedView::rightButtonClicked() {
    Serial.println("right button clicked");
};

void DisconnectedView::okButtonClicked() {
    Serial.println("ok button clicked");
    manager->show(SETUP_VIEW);
};

void DisconnectedView::update() {
    LayoutBase::update();

    if(manager->webserver->hasInternetAccess) {
        manager->show(MAIN_VIEW);
    }
}