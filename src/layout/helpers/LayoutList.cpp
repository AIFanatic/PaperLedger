#include "LayoutList.h"

LayoutList::LayoutList(Render *_render) {
    render = _render;
};

LayoutList::~LayoutList() {
};

void LayoutList::init(int _x, int _y, int _w, int _h, int _fontSize, int _color) {
    x = _x;
    y = _y;
    w = _w;
    h = _h;
    fontSize = _fontSize;
    color = _color;

    render->setFont(fontSize);
    render->getTextBounds(x, y, "Hey|", textWidth, textHeight);

    activeRow = 0;
}

void LayoutList::removeAll() {
    for(int i = 0; i < rowLen; i++) {
        rows[rowLen][TEXT] = "";
        rows[rowLen][IDENTIFIER] = "";
    }

    rowLen = 0;
}

void LayoutList::add(String text, String identifier) {
    rows[rowLen][TEXT] = text;
    rows[rowLen][IDENTIFIER] = identifier;
    rowLen++;
}

void LayoutList::addFromArray(String arr[][2], int size) {
    for(int i = 0; i < size; i++) {
        rows[rowLen][TEXT] = arr[i][TEXT];
        rows[rowLen][IDENTIFIER] = arr[i][IDENTIFIER];
        rowLen++;
    }
}

void LayoutList::setActive(int index) {
    if(index >= 0 && index <= rowLen) {
        activeRow = index;
        draw();
    }
}

int LayoutList::getActiveIndex() {
    return activeRow;
}

String LayoutList::getActiveText() {
    return rows[activeRow][TEXT];
}

String LayoutList::getActiveIdentifier() {
    return rows[activeRow][IDENTIFIER];
}

int LayoutList::getCount() {
    return rowLen - 1;
}

void LayoutList::draw() {
    // // Draw boundary
    // render->drawRectangle(x, y, w, h, !color, true);

    render->drawRectangle(x, y, w, h, !color, true);

    // Start where bounding box starts
    // Custom font starts at the bottom, while
    // system font starts at the top
    // int currentHeight = y + textHeight - textMargin;
    int currentHeight = y + textHeight;

    // Draw rows
    for(int i = 0; i < rowLen; i++) {
        // int tY = y + textHeight;

        int textColor = color;



        if(i == activeRow) {
            // Custom font starts at the bottom, thus need to
            // subtract by textHeight
            // To center bounding box, need to add margin
            render->drawRectangle(x, currentHeight - textHeight + (textHeight / 4), w, textHeight, color, true);
            textColor = !color;
        }

        render->drawText(x + textMargin , currentHeight, rows[i][TEXT].c_str(), fontSize, textColor);

        currentHeight += textHeight;
    }

    // render->draw();
    render->draw(x, y, w, h, true);
}

void LayoutList::moveUp() {
    int listActiveIndex = getActiveIndex();
    listActiveIndex--;

    if(listActiveIndex < 0) {
        listActiveIndex = getCount();
    }

    setActive(listActiveIndex);
}

void LayoutList::moveDown() {
    int listActiveIndex = getActiveIndex();
    listActiveIndex++;

    if(listActiveIndex > getCount()) {
        listActiveIndex = 0;
    }

    setActive(listActiveIndex);
}