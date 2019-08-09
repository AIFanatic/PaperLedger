#include "./app/Manager.h"

Manager *manager;

void setup() {
    Serial.begin(115200);
   
    manager = new Manager();
}

void loop() {
    manager->update();
}

// #include "SPI.h"

// #include "variables.h"

// #include <GxEPD2_BW.h>

// GxEPD2_BW<GxEPD2_290, GxEPD2_290::HEIGHT> display(GxEPD2_290(/*CS=5*/ ELINK_SS, /*DC=*/ ELINK_DC, /*RST=*/ ELINK_RESET, /*BUSY=*/ ELINK_BUSY));

// void showBox(uint16_t x, uint16_t y, uint16_t w, uint16_t h, bool partial)
// {
//   //Serial.println("showBox");
//   display.setRotation(1);
//   if (partial)
//   {
//     display.setPartialWindow(x, y, w, h);
//   }
//   else
//   {
//     display.setFullWindow();
//   }
//   display.firstPage();
//   do
//   {
//     display.fillScreen(GxEPD_WHITE);
//     display.fillRect(x, y, w, h, GxEPD_BLACK);
//   }
//   while (display.nextPage());
// }

// void setup()
// {
//   Serial.begin(115200);
//   Serial.println();
//   Serial.println("setup");
//   delay(100);
//   SPI.begin(SPI_CLK, SPI_MISO, SPI_MOSI, -1);
//   display.init(115200);
//   // first update should be full refresh
//   showBox(16, 16, 48, 32, false);
//   showBox(16, 56, 48, 32, true);
// }

// void loop()
// {
// }