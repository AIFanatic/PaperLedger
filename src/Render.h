#ifndef RENDER_H
#define RENDER_H

#include <Arduino.h>

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

        void drawRectangle(int x, int y, int w, int h, int color);
        void drawCircle(int x, int y, int r, int color);
        void drawText(int x, int y, const char *text, int color);
        void drawImage(int index, int x, int y, int w, int h);

        void addImageToFrameCentered(int x, int y, bool startsFromTop = false);
        void addImageToFrame(int x, int y);

    private:
        unsigned char image[2048];
        Paint *paint;
        Epd epd;
};

#endif
