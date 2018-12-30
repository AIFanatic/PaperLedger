#include "LayoutList.h"

LayoutList::LayoutList(Render *_render) {
    render = _render;
};

LayoutList::~LayoutList() {
};

void LayoutList::init(int _x, int _y, int _w, int _h, int _fontSize) {
    x = _x;
    y = _y;
    w = _w;
    h = _h;
    fontSize = _fontSize;

    activeRow = 0;
}

void LayoutList::add(const char *text) {
    rows[rowLen] = text;
    rowLen++;
}

void LayoutList::setActive(int index) {
    if(index >= 0 && index <= rowLen) {
        activeRow = index;
        draw();
    }
}

int LayoutList::getActive() {
    return activeRow;
}

void LayoutList::draw() {
    // // Draw boundary
    // render->drawRectangle(x, y, w, h, BLACK);
    // render->addImageToFrame(x, y);

    // Draw rows
    for(int i = 0; i < rowLen; i++) {
        int tX = x;
        int tY = h - (i * (fontSize + 2)); // TODO: Different fontSize messes up

        int color = BLACK;

        if(i == activeRow) {
            color = WHITE;
        }

        render->drawText(0, 0, rows[i].c_str(), fontSize, color, w, fontSize);
        render->addImageToFrame(tX, tY);
    }

    render->draw();
}