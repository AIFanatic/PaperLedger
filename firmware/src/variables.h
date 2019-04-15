#ifndef Variables_h
#define Variables_h

#include <pgmspace.h>

// BOARD PINS
#define ELINK_BUSY 4
#define ELINK_RESET 12
#define ELINK_DC 19
#define ELINK_SS 5

#define SPI_MOSI 23
#define SPI_MISO 2
#define SPI_CLK 18

#define SDCARD_SS 13
#define BUTTON_1 38
#define BUTTON_2 37
#define BUTTON_3 39

#define SPEAKER_PIN_PIN 25

#define LEFT_BUTTON GPIO_NUM_39
#define RIGHT_BUTTON GPIO_NUM_37
#define OK_BUTTON GPIO_NUM_38

// DISPLAY
#define BLACK 0
#define WHITE 1

#define NO_ALIGNMENT 0
#define LEFT_ALIGNMENT 1
#define RIGHT_ALIGNMENT 2
#define CENTER_ALIGNMENT 3

// VIEWS
enum VIEWS {
    MAIN_VIEW,
    TICKER_VIEW,
    SETUP_VIEW,
    DISCONNECTED_VIEW,
    LOADING_VIEW,
    UPDATE_VIEW
};

// PROVIDERS
enum PROVIDERS {
    COIN_GECKO = 0,
    BITCOIN_AVERAGE = 1,
    COUNT = 2
};

// FILENAMES
#define FILE_SETTINGS "/settings.json"
#define FILE_TICKERS "/tickers.json"

// NETWORK
#define AP_NAME "PaperLedger"
#define AP_IP "192.168.1.1"

// ENDPOINTS
#define URL_IM_ALIVE "https://api.ipify.org/"

// SETTINGS
#define DATA_SOURCE "data_source"
#define DEFAULT_SETTINGS "{\"ssid\":\"\",\"password\":\"\",\"tickers_update_frequency\":60,\"tickers_scroll_frequency\":10,\"mute_speakers\": \"false\", \"" DATA_SOURCE "\": \"0\"}"

#endif