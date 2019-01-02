#ifndef LayoutSetup_H
#define LayoutSetup_H

#include "../Render.h"
#include "../Manager.h"
#include "../helpers/LayoutBase.h"
#include "../helpers/LayoutList.h"

#include <HTTPClient.h>
#include <ArduinoJson.h>

#define SIZEOFARRAY(x)  (sizeof(x) / sizeof((x)[0]))

class LayoutSetup: public LayoutBase {
    public:
        LayoutSetup(Manager *_manager);
        ~LayoutSetup(void);

    private:        
        void initMenu();
        void showMenu(const char *menu[][2], int size);

        void leftButtonClicked();
        void rightButtonClicked();
        void okButtonClicked();

        void getTickers();

        LayoutList *menuList;

        // {TEXT, IDENTIFIER}
        const char *MAIN_MENU[5][2] = 
        {
            {"Tickers", "TICKERS"}, 
            {"Customize", "CUSTOMIZE"},
            {"Network", "NETWORK"},
            {"Reset", "RESET"},
            {"Back", "BACK"},
        };

        const char *TICKERS_MENU[3][2] = 
        {
            {"Add ticker", "ADD_TICKER"}, 
            {"Remove ticker", "REMOVE_TICKER"},
            {"Back", "BACK_TICKER"}    
        };

        int tickersCurrentPage = 1;

};

#endif