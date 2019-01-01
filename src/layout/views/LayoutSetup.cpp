#include "LayoutSetup.h"

LayoutSetup::LayoutSetup(Display *_display): LayoutBase(_display) {
    initMenu();
    showMenu(MAIN_MENU, SIZEOFARRAY(MAIN_MENU));
};

LayoutSetup::~LayoutSetup() {
};

void LayoutSetup::initMenu() {
    menuRoot = new MenuBackend(menuUseEventStatic, menuChangeEventStatic, this);
    
    menuRoot->getRoot().add(TICKERS);
    TICKERS.addAfter(CUSTOMIZE);
        TICKERS.addRight(ADD_TICKER);
        ADD_TICKER.addAfter(REMOVE_TICKER);
        REMOVE_TICKER.addAfter(BACK_TICKER);
    CUSTOMIZE.addAfter(NETWORK);
    NETWORK.addAfter(BACK);

    // wrap
    TICKERS.addBefore(BACK);
        ADD_TICKER.addBefore(BACK_TICKER);
        BACK_TICKER.addAfter(ADD_TICKER);
    BACK.addAfter(TICKERS);

    // Init list
    menuList = new LayoutList(display->render);
    menuList->init(0, 0, 296, 120, 12, BLACK);
    
    // Move from root to first menu
    menuRoot->moveDown();
}

void LayoutSetup::showMenu(const char *menu[], int size) {
    menuList->removeAll();
    menuList->addFromArray(menu, size);

    menuList->setActive(0);
}

void LayoutSetup::menuChangeEventStatic(MenuChangeEvent changed, void *context) {
    LayoutSetup *instance = (LayoutSetup *)context;
    instance->menuChangeEvent(changed);
}

void LayoutSetup::menuChangeEvent(MenuChangeEvent changed) {
	Serial.print("Menu change ");
	Serial.print(changed.from.getName());
	Serial.print(" ");
	Serial.println(changed.to.getName());

    // const char *name = changed.to.getName();
}

void LayoutSetup::menuUseEventStatic(MenuUseEvent used, void *context) {
    LayoutSetup *instance = (LayoutSetup *)context;
    instance->menuUseEvent(used);
}

void LayoutSetup::menuUseEvent(MenuUseEvent used) {
    const char *name = used.item.getName();

    Serial.print("Menu use ");
	Serial.println(name);

    if(strcmp(name, "TICKERS") == 0) {
        menuRoot->moveRight();
        showMenu(TICKERS_MENU, SIZEOFARRAY(TICKERS_MENU));
    }
    else if(strcmp(name, "BACK") == 0) {
        display->show(LAYOUT_TICKER);
    }
    else if(strcmp(name, "BACK_TICKER") == 0) {
        menuRoot->moveLeft();
        showMenu(MAIN_MENU, SIZEOFARRAY(MAIN_MENU));
    }
}




void LayoutSetup::leftButtonClicked() {
    Serial.println("left button clicked");

    menuRoot->moveUp();
    menuList->moveUp();
};

void LayoutSetup::rightButtonClicked() {
    Serial.println("right button clicked");

    menuRoot->moveDown();
    menuList->moveDown();
};

void LayoutSetup::okButtonClicked() {
    menuRoot->use();
    Serial.println("ok button clicked");
};