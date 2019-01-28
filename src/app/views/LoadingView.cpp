#include "LoadingView.h"

LoadingView::LoadingView(Manager *_manager): LayoutBase(_manager) {
    String title = "Welcome to ";
    title.concat(AP_NAME);

    manager->render->fillScreen(WHITE);
    manager->render->drawRectangle(0, 0, 296, 50, BLACK, 1);
    manager->render->drawText(0, 35, title.c_str(), 12, WHITE, CENTER_ALIGNMENT);
    manager->render->drawText(0, 85, "Attempting to connect", 9, BLACK, CENTER_ALIGNMENT);
    manager->render->drawText(0, 110, "to the Internet" , 9, BLACK, CENTER_ALIGNMENT);
    manager->render->draw();
};

LoadingView::~LoadingView() {
};

void LoadingView::leftButtonClicked() {
};

void LoadingView::rightButtonClicked() {
};

void LoadingView::okButtonClicked() {
    manager->show(SETUP_VIEW);
};

void LoadingView::update() {
    LayoutBase::update();

    if(manager->webserver->hasInternetAccess) {
        manager->show(MAIN_VIEW);
    }
}