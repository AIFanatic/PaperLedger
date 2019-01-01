#include "Manager.h"
#include "./views/LayoutTicker.h"
#include "./views/LayoutSetup.h"

Manager::Manager() {
    // Init render
    render = new Render();
    render->clearScreen();

    // Init filesystem
    filesystem = new FileSystem();
};

Manager::~Manager() {
};

// TODO: Ugly, fix
void Manager::show(int index) {
    if(currentLayout) {
        currentLayout = nullptr;
    }

    if(index == LAYOUT_TICKER) {
        currentLayout = new LayoutTicker(this);
    }
    else if(index == LAYOUT_SETUP) {
        currentLayout = new LayoutSetup(this);
    }

    currentIndex = index;
};

// TODO: Ugly, fix
void Manager::update() {
    if(currentIndex == LAYOUT_TICKER) {
        (reinterpret_cast<LayoutTicker *>(currentLayout))->update();
    }
    else if(currentIndex == LAYOUT_SETUP) {
        (reinterpret_cast<LayoutSetup *>(currentLayout))->update();
    }
}