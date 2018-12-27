#include <SPI.h>
#include <./libraries/epd2in9.h>
#include <./libraries/epdpaint.h>
#include "imagedata.h"

#define COLORED     0
#define UNCOLORED   1

/**
  * Due to RAM not enough in Arduino UNO, a frame buffer is not allowed.
  * In this case, a smaller image buffer is allocated and you have to 
  * update a partial display several times.
  * 1 byte = 8 pixels, therefore you have to set 8*N pixels at a time.
  */
unsigned char image[2048];
Paint paint(image, 0, 0);    // width should be the multiple of 8 
Epd epd;
unsigned long time_start_ms;
unsigned long time_now_s;

void clearScreen() {
    paint.SetWidth(128);
    paint.SetHeight(128);
    paint.SetRotate(ROTATE_90);

    paint.Clear(UNCOLORED);
    epd.SetFrameMemory(paint.GetImage(), 0, 0, paint.GetWidth(), paint.GetHeight());
    epd.SetFrameMemory(paint.GetImage(), 0, 128, paint.GetWidth(), paint.GetHeight());
    epd.SetFrameMemory(paint.GetImage(), 0, 256, paint.GetWidth(), paint.GetHeight());
    epd.DisplayFrame();

    paint.Clear(COLORED);
    epd.SetFrameMemory(paint.GetImage(), 0, 0, paint.GetWidth(), paint.GetHeight());
    epd.SetFrameMemory(paint.GetImage(), 0, 128, paint.GetWidth(), paint.GetHeight());
    epd.SetFrameMemory(paint.GetImage(), 0, 256, paint.GetWidth(), paint.GetHeight());
    epd.DisplayFrame();

    epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
    epd.DisplayFrame();

    epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
    epd.DisplayFrame();
}

void drawRectangle(int w, int h, int x, int y) {
    paint.SetWidth(w+8);
    paint.SetHeight(h+8);
    paint.SetRotate(ROTATE_90);

    paint.Clear(UNCOLORED);
    paint.DrawRectangle(4, 4, w+4, h+4, COLORED);
    epd.SetFrameMemory(paint.GetImage(), x - ((w+8)/2), y - ((h+8)/2), paint.GetWidth(), paint.GetHeight()); // Flip coordinates
}

void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
    if (epd.Init(lut_full_update) != 0) {
        Serial.print("e-Paper init failed");
        return;
    }

    /** 
     *  there are 2 memory areas embedded in the e-paper display
     *  and once the display is refreshed, the memory area will be auto-toggled,
     *  i.e. the next action of SetFrameMemory will set the other memory area
     *  therefore you have to clear the frame memory twice.
     */
    epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
    epd.DisplayFrame();

    epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
    epd.DisplayFrame();

    if (epd.Init(lut_partial_update) != 0) {
        Serial.print("e-Paper init failed");
        return;
    }

    clearScreen();
}

void loop() {
    drawRectangle(64, 64, 64, 64);
    drawRectangle(64, 64, 64, 144);
    drawRectangle(64, 64, 64, 224);

    epd.DisplayFrame();

    delay(500);
}