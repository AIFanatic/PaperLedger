#ifndef Variables_h
#define Variables_h

#include <pgmspace.h>


// TOODO: Port somewhere else
#define LEFT_BUTTON GPIO_NUM_39
#define RIGHT_BUTTON GPIO_NUM_37
#define OK_BUTTON GPIO_NUM_38


enum LAYOUTS {
    LAYOUT_MAIN,
    LAYOUT_TICKER,
    LAYOUT_SETUP,
    LAYOUT_DISCONNECTED
};

#define FILE_SETTINGS "/settings.json"
#define FILE_TICKERS "/tickers.json"

#define AP_NAME "inkCrypto"
#define AP_IP "192.168.1.1"

#define URL_IM_ALIVE "https://api.ipify.org/"
#define URL_TICKER_DATA "https://api.coingecko.com/api/v3/simple/price?include_24hr_vol=true&include_24hr_change=true&include_last_updated_at=true&include_24hr_vol=true"

#define DEFAULT_SETTINGS "{\"ssid\":\"\",\"password\":\"\",\"tickers_last_update\":0,\"tickers_update_frequency\":60,\"tickers_scroll_frequency\":10}"

#endif