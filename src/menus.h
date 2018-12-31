#ifndef _MENUS_H_
#define _MENUS_H_

#include <pgmspace.h>

const unsigned char _MENU_MAIN[] PROGMEM = "[{\"type\": \"fill\", \"color\": 1},{\"type\":\"rectangle\",\"x\":0,\"y\":0,\"w\":128,\"h\":128,\"color\":0},{\"type\":\"text\",\"x\":150,\"y\":24,\"text\":\"28 DEC 2018\",\"size\":9,\"color\":0},{\"type\":\"text\",\"x\":35,\"y\":110,\"text\":\"SEND\",\"size\":12,\"color\":0},{\"type\":\"image\",\"x\":32,\"y\":25,\"w\":64,\"h\":64,\"index\":5,\"color\":0,\"mode\":2}]";
const unsigned char _MENU_SEND[] PROGMEM = "[{\"type\": \"fill\", \"color\": 1},{\"type\":\"rectangle\",\"x\":0,\"y\":0,\"w\":128,\"h\":128,\"color\":0},{\"type\":\"text\",\"x\":150,\"y\":24,\"text\":\"28 DEC 2018\",\"size\":9,\"color\":0},{\"type\":\"text\",\"x\":35,\"y\":110,\"text\":\"SEND\",\"size\":12,\"color\":0},{\"type\":\"image\",\"x\":32,\"y\":25,\"w\":64,\"h\":64,\"index\":5,\"color\":0,\"mode\":2}]";
const unsigned char _MENU_RECEIVE[] PROGMEM = "[{\"type\": \"fill\", \"color\": 1},{\"type\":\"rectangle\",\"x\":0,\"y\":0,\"w\":128,\"h\":128,\"color\":0},{\"type\":\"text\",\"x\":150,\"y\":24,\"text\":\"28 DEC 2018\",\"size\":9,\"color\":0},{\"type\":\"text\",\"x\":15,\"y\":110,\"text\":\"RECEIVE\",\"size\":12,\"color\":0},{\"type\":\"image\",\"x\":32,\"y\":25,\"w\":64,\"h\":64,\"index\":4,\"color\":0,\"mode\":2}]";
const unsigned char _MENU_SETUP[] PROGMEM = "[{\"type\": \"fill\", \"color\": 1},{\"type\":\"rectangle\",\"x\":0,\"y\":0,\"w\":128,\"h\":128,\"color\":0},{\"type\":\"text\",\"x\":150,\"y\":24,\"text\":\"28 DEC 2018\",\"size\":9,\"color\":0},{\"type\":\"text\",\"x\":25,\"y\":110,\"text\":\"SETUP\",\"size\":12,\"color\":0},{\"type\":\"image\",\"x\":32,\"y\":25,\"w\":64,\"h\":64,\"index\":7,\"color\":0,\"mode\":2}]";
const unsigned char _MENU_WIFI[] PROGMEM = "[{\"type\": \"fill\", \"color\": 1},{\"type\":\"rectangle\",\"x\":0,\"y\":0,\"w\":128,\"h\":128,\"color\":0},{\"type\":\"text\",\"x\":150,\"y\":24,\"text\":\"28 DEC 2018\",\"size\":9,\"color\":0},{\"type\":\"text\",\"x\":35,\"y\":110,\"text\":\"WIFI\",\"size\":12,\"color\":0},{\"type\":\"image\",\"x\":32,\"y\":25,\"w\":64,\"h\":64,\"index\":9,\"color\":0,\"mode\":2}]";
const unsigned char _MENU_WALLET[] PROGMEM = "[{\"type\": \"fill\", \"color\": 1},{\"type\":\"rectangle\",\"x\":0,\"y\":0,\"w\":128,\"h\":128,\"color\":0},{\"type\":\"text\",\"x\":150,\"y\":24,\"text\":\"28 DEC 2018\",\"size\":9,\"color\":0},{\"type\":\"text\",\"x\":25,\"y\":110,\"text\":\"WALLET\",\"size\":12,\"color\":0},{\"type\":\"image\",\"x\":32,\"y\":25,\"w\":64,\"h\":64,\"index\":8,\"color\":0,\"mode\":2}]";
const unsigned char _MENU_BACK[] PROGMEM = "[{\"type\": \"fill\", \"color\": 1},{\"type\":\"rectangle\",\"x\":0,\"y\":0,\"w\":128,\"h\":128,\"color\":0},{\"type\":\"text\",\"x\":150,\"y\":24,\"text\":\"28 DEC 2018\",\"size\":9,\"color\":0},{\"type\":\"text\",\"x\":35,\"y\":110,\"text\":\"BACK\",\"size\":12,\"color\":0},{\"type\":\"image\",\"x\":32,\"y\":25,\"w\":64,\"h\":64,\"index\":0,\"color\":0,\"mode\":2}]";

#define MENU_MAIN _MENU_MAIN
    #define MENU_SEND _MENU_SEND
    #define MENU_RECEIVE _MENU_RECEIVE
    #define MENU_SETUP _MENU_SETUP
        #define MENU_WIFI _MENU_WIFI
        #define MENU_WALLET _MENU_WALLET
        #define MENU_BACK _MENU_BACK

#endif


// TOODO: Port somewhere else
#define LEFT_BUTTON GPIO_NUM_37
#define RIGHT_BUTTON GPIO_NUM_39
#define OK_BUTTON GPIO_NUM_38


enum DISPLAYS {
    LAYOUT_MAIN,
    LAYOUT_WIFI
};