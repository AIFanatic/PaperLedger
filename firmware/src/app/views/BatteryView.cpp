#include "BatteryView.h"

BatteryView::BatteryView(Manager *_manager): LayoutBase(_manager) {
    manager->render->fillScreen(WHITE);
    manager->render->drawRectangle(0, 0, 296, 50, BLACK, 1);
    manager->render->drawText(0, 35, "Battery running low", 18, WHITE, CENTER_ALIGNMENT);
    manager->render->drawText(0, 85, "Please charge your device", 9, BLACK, CENTER_ALIGNMENT);
    manager->render->drawText(0, 110, "by connecting the USB cable" , 9, BLACK, CENTER_ALIGNMENT);
    manager->render->draw();
};

BatteryView::~BatteryView() {
};

void BatteryView::leftButtonClicked() {
};

void BatteryView::rightButtonClicked() {
};

void BatteryView::okButtonClicked() {
};

void BatteryView::update() {
    LayoutBase::update();

    if(manager->battery->isCharging) {
        manager->show(MAIN_VIEW);
    }
}