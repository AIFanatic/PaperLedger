#include "Display.h"
#include "./views/LayoutTicker.h"
#include "./views/LayoutSetup.h"

Display::Display() {
    // Init render
    render = new Render();
    render->clearScreen();

    // Init filesystem
    filesystem = new FileSystem();
};

Display::~Display() {
};

// TODO: Ugly, fix
void Display::show(int index) {
    if(currentDisplay) {
        currentDisplay = nullptr;
    }

    if(index == LAYOUT_TICKER) {
        currentDisplay = new LayoutTicker(this);
    }
    else if(index == LAYOUT_SETUP) {
        currentDisplay = new LayoutSetup(this);
    }

    currentIndex = index;
};

// TODO: Ugly, fix
void Display::update() {
    if(currentIndex == LAYOUT_TICKER) {
        (reinterpret_cast<LayoutTicker *>(currentDisplay))->update();
    }
    else if(currentIndex == LAYOUT_SETUP) {
        (reinterpret_cast<LayoutSetup *>(currentDisplay))->update();
    }
}