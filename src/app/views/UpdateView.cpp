#include "UpdateView.h"

UpdateView::UpdateView(Manager *_manager): LayoutBase(_manager) {

    manager->render->fillScreen(WHITE);
    manager->render->drawRectangle(0, 0, 296, 50, BLACK, 1);
    manager->render->drawText(0, 35, "Updating", 18, WHITE, CENTER_ALIGNMENT);
    manager->render->drawText(0, 85, "Your device is being updated", 9, BLACK, CENTER_ALIGNMENT);
    manager->render->drawText(0, 110, "Please do not turn the power off" , 9, BLACK, CENTER_ALIGNMENT);
    manager->render->draw();
};

UpdateView::~UpdateView() {
};

void UpdateView::leftButtonClicked() {
};

void UpdateView::rightButtonClicked() {
};

void UpdateView::okButtonClicked() {
};

void UpdateView::update() {
    LayoutBase::update();
}