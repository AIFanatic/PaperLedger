#ifndef _MENUS_H_
#define _MENUS_H_

#include <pgmspace.h>

const unsigned char _MENU_MAIN[] PROGMEM = "[{\"type\":\"fill\",\"color\":1},{\"type\":\"text\",\"x\":15,\"y\":110,\"text\":\"$3,745.61\",\"size\":24,\"color\":0},{\"type\":\"text\",\"x\":35,\"y\":40,\"text\":\"Bitcoin\",\"size\":24,\"color\":0}]";
const unsigned char _MENU_TICKER[] PROGMEM = "[{\"type\":\"fill\",\"color\":1},{\"type\":\"text\",\"x\":15,\"y\":110,\"text\":\"$3,745.61\",\"size\":24,\"color\":0},{\"type\":\"text\",\"x\":35,\"y\":40,\"text\":\"Bitcoin\",\"size\":24,\"color\":0}]";
const unsigned char _MENU_SETUP[] PROGMEM = "[{\"type\": \"fill\", \"color\": 1},{\"type\":\"rectangle\",\"x\":0,\"y\":0,\"w\":128,\"h\":128,\"color\":0},{\"type\":\"text\",\"x\":150,\"y\":24,\"text\":\"28 DEC 2018\",\"size\":9,\"color\":0},{\"type\":\"text\",\"x\":25,\"y\":110,\"text\":\"SETUP\",\"size\":12,\"color\":0},{\"type\":\"image\",\"x\":32,\"y\":25,\"w\":64,\"h\":64,\"index\":7,\"color\":0,\"mode\":2}]";

#define MENU_MAIN _MENU_MAIN
    #define MENU_TICKER _MENU_SEND
    #define MENU_SETUP _MENU_SETUP

#endif


// TOODO: Port somewhere else
#define LEFT_BUTTON GPIO_NUM_37
#define RIGHT_BUTTON GPIO_NUM_39
#define OK_BUTTON GPIO_NUM_38


enum DISPLAYS {
    LAYOUT_TICKER,
    LAYOUT_SETUP
};

#define FILE_SETTINGS "/settings.json"
#define FILE_TICKERS "/tickers.json"

#define AP_NAME "inkCrypto"
#define AP_IP "192.168.1.1"

#define URL_IM_ALIVE "https://api.ipify.org/"