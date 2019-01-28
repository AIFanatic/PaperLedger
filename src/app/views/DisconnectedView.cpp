#include "DisconnectedView.h"

DisconnectedView::DisconnectedView(Manager *_manager, int _prevLayoutIndex): LayoutBase(_manager) {
    manager->render->fillScreen(WHITE);
    manager->render->drawText(35, 40, "No Internet", 18, BLACK);

    String networkName = "Network name: ";
    String networkIP = "Web Portal: http://";

    networkName.concat(AP_NAME);
    networkIP.concat(AP_NAME);
    networkIP.concat(".local");

    manager->render->fillScreen(1);
    manager->render->drawRectangle(0, 0, 296, 50, BLACK, 1);
    manager->render->drawText(0, 35, "No Internet", 18, WHITE, CENTER_ALIGNMENT);
    manager->render->drawText(0, 85, networkName.c_str(), 9, BLACK, CENTER_ALIGNMENT);
    manager->render->drawText(0, 110, networkIP.c_str() , 9, BLACK, CENTER_ALIGNMENT);
    manager->render->draw();

    prevLayoutIndex = _prevLayoutIndex;
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
        manager->show(prevLayoutIndex);
    }
}