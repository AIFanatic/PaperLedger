#include "Display.h"
#include "./views/LayoutMain.h"
#include "./views/LayoutWifi.h"
#include "./views/LayoutReceive.h"

Display::Display() {
    // Init render
    render = new Render();
    render->clearScreen();

    // Init filesystem
    filesystem = new FileSystem();

    // Init wallet
    wallet = new Wallet(filesystem);
};

Display::~Display() {
};

// TODO: Ugly, fix
void Display::show(int index) {
    if(currentDisplay) {
        currentDisplay = nullptr;
    }

    if(index == LAYOUT_MAIN) {
        currentDisplay = new LayoutMain(this);
    }
    else if(index == LAYOUT_WIFI) {
        currentDisplay = new LayoutWifi(this);
    }
    else if(index == LAYOUT_RECEIVE) {
        currentDisplay = new LayoutReceive(this);
    }

    currentIndex = index;
};

// TODO: Ugly, fix
void Display::update() {
    if(currentIndex == LAYOUT_MAIN) {
        (reinterpret_cast<LayoutMain *>(currentDisplay))->update();
    }
    else if(currentIndex == LAYOUT_WIFI) {
        (reinterpret_cast<LayoutWifi *>(currentDisplay))->update();
    }
    else if(currentIndex == LAYOUT_RECEIVE) {
        (reinterpret_cast<LayoutReceive *>(currentDisplay))->update();
    }
}