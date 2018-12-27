#if defined(ESP8266) || defined(ESP32)
#include <pgmspace.h>
#else
#include <pgmspace.h>
#endif
// 24 x 24 gridicons_attachment
const unsigned char gridicons_attachment[] PROGMEM = { /* 0X01,0X01,0XB4,0X00,0X40,0X00, */
0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0xFF, 0xFC, 0x03, 
0xFF, 0xFC, 0x73, 0xFF, 0xF9, 0xF1, 0xFF, 0xF9, 
0xF9, 0xFF, 0xF9, 0x99, 0xFF, 0xF9, 0x99, 0xFF, 
0xF9, 0x99, 0xFF, 0xF9, 0x99, 0xFF, 0xF9, 0x99, 
0xFF, 0xF9, 0x99, 0x9F, 0xF9, 0x99, 0x9F, 0xF9, 
0x99, 0x9F, 0xF9, 0x99, 0x9F, 0xF9, 0x99, 0x9F, 
0xF9, 0x99, 0x9F, 0xF9, 0x81, 0x9F, 0xFC, 0xE3, 
0x3F, 0xFC, 0xFE, 0x3F, 0xFE, 0x3C, 0x7F, 0xFF, 
0x00, 0xFF, 0xFF, 0x81, 0xFF, 0xFF, 0xFF, 0xFF
};
