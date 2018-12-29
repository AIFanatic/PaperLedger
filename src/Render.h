#ifndef RENDER_H
#define RENDER_H

#include <epd2in9.h>
#include <epdpaint.h>
#include <ArduinoJson.h>

#include "icons.h"

#define BLACK 0
#define WHITE 1

class Render {
    public:
        Render(void);
        ~Render(void);

        void initDisplay();
        void clearScreen();
        void clearBuffer();
        void drawFromJson(String json);

        void drawRectangle(int x, int y, int w, int h, int color, bool filled = false);
        void drawCircle(int x, int y, int r, int color, bool filled = false);
        void drawText(int x, int y, const char *text, int size, int color);
        void drawText(int x, int y, const char *text, int size, int color, int w, int h);
        void drawImage(int index, int x, int y, int w, int h);

        void addImageToFrame(int x, int y);

        void draw();

    private:
        unsigned char image[2048];
        Paint *paint;
        Epd epd;
};

#endif
