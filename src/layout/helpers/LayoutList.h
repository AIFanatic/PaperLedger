#ifndef LAYOUTLIST_H
#define LAYOUTLIST_H

#include "../Render.h"

class LayoutList {
    public:
        LayoutList(Render *render);
        ~LayoutList(void);

        void init(int _x, int _y, int _w, int _h, int _fontSize, int _color);
        void removeAll();
        void add(const char *text, const char *identifier);
        void addFromArray(const char *arr[][2], int size);
        void setActive(int index);

        const char *getActiveText();
        const char *getActiveIdentifier();
        int getActiveIndex();
        int getCount();

        void moveUp();
        void moveDown();

        void draw();

    private:
        Render *render;

        const char *rows[20][2];
        int rowLen = 0;

        int x;
        int y;
        int w;
        int h;
        int fontSize;
        int color;

        uint16_t textWidth;
        uint16_t textHeight;
        int textMargin = 4;

        int activeRow;

        enum INFO {
            TEXT,
            IDENTIFIER
        };
};

#endif