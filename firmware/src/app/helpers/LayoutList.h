#ifndef LAYOUTLIST_H
#define LAYOUTLIST_H

#include "../controller/Render.h"

class LayoutList {
    public:
        LayoutList(Render *render);
        ~LayoutList(void);

        void init(int _x, int _y, int _w, int _h, int _fontSize, int _color);
        void removeAll();
        void add(String text, String identifier);
        void addFromArray(String arr[][2], int size);
        void setActive(int index);

        String getActiveText();
        String getActiveIdentifier();
        int getActiveIndex();
        int getCount();

        void moveUp();
        void moveDown();

        void draw();

    private:
        Render *render;

        String rows[20][2];
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