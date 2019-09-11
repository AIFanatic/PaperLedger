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

#define SPEAKER_PIN 25
#define SPEAKER_POWER_PIN 27

#define LEFT_BUTTON GPIO_NUM_39
#define RIGHT_BUTTON GPIO_NUM_37
#define OK_BUTTON GPIO_NUM_38

#define RED_LED_PIN 26
#define VBAT_PIN 34
#define CHARGE_PIN 33

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
    UPDATE_VIEW,
    BATTERY_VIEW
};

// FILENAMES
#define FILE_SETTINGS "/settings.json"
#define FILE_TICKERS "/tickers.json"

// NETWORK
#define AP_NAME "PaperLedger"
#define AP_IP "192.168.4.1"

// ENDPOINTS
#define URL_IM_ALIVE "https://ipapi.co/json/"
#define URL_TICKER_DATA "https://api.coingecko.com/api/v3/simple/price?include_24hr_vol=true&include_24hr_change=true&include_last_updated_at=true&include_24hr_vol=true"

// SETTINGS
#define DEFAULT_SETTINGS "{\"ssid\":\"\",\"password\":\"\",\"utc_offset\":0,\"tickers_update_frequency\":60000,\"tickers_scroll_frequency\":10000,\"mute_speakers\": \"true\"}"

#define BATTERY_WARNING_PERCENTAGE 20
#define BATTERY_CHARGED_PERCENTAGE 90
#define BATTERY_CHECK_FREQUENCY_MS 10000
#define BATTERY_FULL_CHARGE_ADC 2365
#define BATTERY_ZERO_CHARGE_ADC 1610
#define BATTERY_CHARGE_DIFFERENCE_ADC 115

#define MIN_AWAKE_TIME_MS 60000

// RTC only supports 16bit, therefore for longs an extra offset needs to be reserved
// in order to prevent data from being overwritten
enum RTC_STORAGE {
    CURRENT_VIEW_INDEX,
    TICKER_INDEX,
    TICKER_LAST_TICKERS_UPDATE,
    TICKER_LAST_TICKERS_UPDATE_RESERVED,
    TICKER_LAST_SCROLL_UPDATE,
    TICKER_LAST_SCROLL_UPDATE_RESERVED
};

#endif