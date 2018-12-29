#ifndef _MENUS_H_
#define _MENUS_H_

#include <pgmspace.h>

const unsigned char _MENU_MAIN[] PROGMEM = "[{\"type\":\"text\",\"x\":150,\"y\":110,\"text\":\"28 DEC 2018\",\"size\":16,\"color\":0},{\"type\":\"rectangle\",\"x\":0,\"y\":0,\"w\":120,\"h\":120,\"color\":0},{\"type\":\"text\",\"x\":35,\"y\":10,\"text\":\"SEND\",\"size\":20,\"color\":0},{\"type\":\"image\",\"x\":32,\"y\":40,\"w\":64,\"h\":64,\"index\":5}]";
const unsigned char _MENU_SEND[] PROGMEM = "[{\"type\":\"text\",\"x\":150,\"y\":110,\"text\":\"28 DEC 2018\",\"size\":16,\"color\":0},{\"type\":\"rectangle\",\"x\":0,\"y\":0,\"w\":120,\"h\":120,\"color\":0},{\"type\":\"text\",\"x\":35,\"y\":10,\"text\":\"SEND\",\"size\":20,\"color\":0},{\"type\":\"image\",\"x\":32,\"y\":40,\"w\":64,\"h\":64,\"index\":5}]";
const unsigned char _MENU_RECEIVE[] PROGMEM = "[{\"type\":\"text\",\"x\":150,\"y\":110,\"text\":\"28 DEC 2018\",\"size\":16,\"color\":0},{\"type\":\"rectangle\",\"x\":0,\"y\":0,\"w\":120,\"h\":120,\"color\":0},{\"type\":\"text\",\"x\":15,\"y\":10,\"text\":\"RECEIVE\",\"size\":20,\"color\":0},{\"type\":\"image\",\"x\":32,\"y\":40,\"w\":64,\"h\":64,\"index\":4}]";
const unsigned char _MENU_SETUP[] PROGMEM = "[{\"type\":\"text\",\"x\":150,\"y\":110,\"text\":\"28 DEC 2018\",\"size\":16,\"color\":0},{\"type\":\"rectangle\",\"x\":0,\"y\":0,\"w\":120,\"h\":120,\"color\":0},{\"type\":\"text\",\"x\":30,\"y\":10,\"text\":\"SETUP\",\"size\":20,\"color\":0},{\"type\":\"image\",\"x\":32,\"y\":40,\"w\":64,\"h\":64,\"index\":7}]";
const unsigned char _MENU_WIFI[] PROGMEM = "[{\"type\":\"text\",\"x\":150,\"y\":110,\"text\":\"28 DEC 2018\",\"size\":16,\"color\":0},{\"type\":\"rectangle\",\"x\":0,\"y\":0,\"w\":120,\"h\":120,\"color\":0},{\"type\":\"text\",\"x\":30,\"y\":10,\"text\":\"WIFI\",\"size\":20,\"color\":0},{\"type\":\"image\",\"x\":32,\"y\":40,\"w\":64,\"h\":64,\"index\":9}]";
const unsigned char _MENU_WALLET[] PROGMEM = "[{\"type\":\"text\",\"x\":150,\"y\":110,\"text\":\"28 DEC 2018\",\"size\":16,\"color\":0},{\"type\":\"rectangle\",\"x\":0,\"y\":0,\"w\":120,\"h\":120,\"color\":0},{\"type\":\"text\",\"x\":20,\"y\":10,\"text\":\"WALLET\",\"size\":20,\"color\":0},{\"type\":\"image\",\"x\":32,\"y\":40,\"w\":64,\"h\":64,\"index\":8}]";
const unsigned char _MENU_BACK[] PROGMEM = "[{\"type\":\"text\",\"x\":150,\"y\":110,\"text\":\"28 DEC 2018\",\"size\":16,\"color\":0},{\"type\":\"rectangle\",\"x\":0,\"y\":0,\"w\":120,\"h\":120,\"color\":0},{\"type\":\"text\",\"x\":35,\"y\":10,\"text\":\"BACK\",\"size\":20,\"color\":0},{\"type\":\"image\",\"x\":32,\"y\":40,\"w\":64,\"h\":64,\"index\":0}]";

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