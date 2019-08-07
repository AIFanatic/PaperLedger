#ifndef RENDER_H
#define RENDER_H

#include <ArduinoJson.h>

#include "icons.h"


#include <GxEPD.h>

#include <GxGDEH029A1/GxGDEH029A1.h>      // 2.9" b/w

// FreeFonts from Adafruit_GFX
#include <fonts/FreeSans7.h>
#include <fonts/FreeSans8.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSans18pt7b.h>
#include <Fonts/FreeSans24pt7b.h>

#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>

#include "SPI.h"

#include "variables.h"

class Render {
    public:
        Render(void);
        ~Render(void);

        void initDisplay();
        void clearScreen(bool partialUpdate = true);
        void drawFromJson(String json);

        void fillScreen(int color);
        void drawRectangle(int x, int y, int w, int h, int color, bool filled = false);
        void drawCircle(int x, int y, int r, int color, bool filled = false);
        void drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, int color, bool filled);
        void drawImage(int index, int x, int y, int w, int h, int color, int mode);
        void drawText(int x, int y, const char *text, int size, int color, int alignment = 0);
        void drawPixel(int x, int y, int color);
        void setFont(int size);

        void getTextBounds(int x, int y, const char *text, uint16_t &w1, uint16_t &h1);

        void draw();
        void draw(int x, int y, int w, int h, bool adjustRotate = false);

    private:
        GxIO_Class *io;
        GxEPD_Class *display;

        int currentFontSize = 0;
};

#endif
