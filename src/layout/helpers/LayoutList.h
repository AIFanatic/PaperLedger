#ifndef LAYOUTLIST_H
#define LAYOUTLIST_H

#include "../Render.h"

class LayoutList {
    public:
        LayoutList(Render *render);
        ~LayoutList(void);

        void init(int _x, int _y, int _w, int _h, int _fontSize, int _color);
        void add(const char *text);
        void setActive(int index);
        int getActive();

        void draw();

    private:
        Render *render;

        String rows[20];
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
};

#endif