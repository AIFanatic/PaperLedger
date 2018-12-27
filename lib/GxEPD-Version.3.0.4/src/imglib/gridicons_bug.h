#if defined(ESP8266) || defined(ESP32)
#include <pgmspace.h>
#else
#include <pgmspace.h>
#endif
// 24 x 24 gridicons_bug
const unsigned char gridicons_bug[] PROGMEM = { /* 0X01,0X01,0XB4,0X00,0X40,0X00, */
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC3, 
0xFF, 0xFF, 0x81, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 
0x00, 0xFF, 0xE7, 0xFF, 0xE7, 0xE7, 0xFF, 0xE7, 
0xE0, 0x00, 0x07, 0xF0, 0x00, 0x0F, 0xFC, 0x18, 
0x3F, 0xFC, 0x18, 0x3F, 0xC0, 0x18, 0x03, 0xC0, 
0x18, 0x03, 0xFC, 0x18, 0x3F, 0xFC, 0x18, 0x3F, 
0xF0, 0x18, 0x0F, 0xE0, 0x18, 0x07, 0xE6, 0x18, 
0x67, 0xE7, 0x18, 0xE7, 0xFF, 0xDB, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};
