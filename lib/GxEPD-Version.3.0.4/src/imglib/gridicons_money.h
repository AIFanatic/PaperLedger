#if defined(ESP8266) || defined(ESP32)
#include <pgmspace.h>
#else
#include <pgmspace.h>
#endif
// 24 x 24 gridicons_money
const unsigned char gridicons_money[] PROGMEM = { /* 0X01,0X01,0XB4,0X00,0X40,0X00, */
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 
0x00, 0x03, 0xC0, 0x00, 0x03, 0xC1, 0xFF, 0x83, 
0xC1, 0xFF, 0x83, 0xC3, 0xE7, 0xC3, 0xCF, 0xC3, 
0xF3, 0xCF, 0xC3, 0xF3, 0xCF, 0xC3, 0xF3, 0xCF, 
0xC3, 0xF3, 0xC3, 0xE7, 0xC3, 0xC1, 0xFF, 0x83, 
0xC1, 0xFF, 0x83, 0xC0, 0x00, 0x03, 0xC0, 0x00, 
0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};
