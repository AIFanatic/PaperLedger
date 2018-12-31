#ifndef RENDER_H
#define RENDER_H

#include <ArduinoJson.h>

#include "icons.h"


#include <GxEPD.h>

#include <GxGDEH029A1/GxGDEH029A1.h>      // 2.9" b/w

// FreeFonts from Adafruit_GFX
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold18pt7b.h>
#include <Fonts/FreeMonoBold24pt7b.h>


#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>

#include "SPI.h"

#define ELINK_BUSY 4
#define ELINK_RESET 12
#define ELINK_DC 19
#define ELINK_SS 5

#define SPI_MOSI 23
#define SPI_MISO 2
#define SPI_CLK 18

#define SDCARD_SS 13





#define BLACK 0
#define WHITE 1

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
        void drawImage(int index, int x, int y, int w, int h, int color, int mode);
        void drawText(int x, int y, const char *text, int size, int color, int w = 0);
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
