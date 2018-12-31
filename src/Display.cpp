#include "Display.h"
#include <LayoutMain.h>
#include <LayoutWifi.h>

Display::Display(Render *_render) {
    render = _render;
    render->clearScreen();
};

Display::~Display() {
};

// TODO: Ugly, fix
void Display::show(int index) {
    if(currentDisplay) {
        currentDisplay = nullptr;
    }

    if(index == LAYOUT_MAIN) {
        currentDisplay = new LayoutMain(render, this);
    }
    else if(index == LAYOUT_WIFI) {
        currentDisplay = new LayoutWifi(render, this);
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
}