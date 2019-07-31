#ifndef SetupView_H
#define SetupView_H

#include "../helpers/LayoutBase.h"
#include "../helpers/LayoutList.h"

#include <HTTPClient.h>
#include <ArduinoJson.h>

#define SIZEOFARRAY(x)  (sizeof(x) / sizeof((x)[0]))

class SetupView: public LayoutBase {
    public:
        SetupView(Manager *_manager);
        ~SetupView(void);

    private:        
        void initMenu();
        void showMenu(String menu[][2], int size);
        void showStatusMenu();

        void leftButtonClicked();
        void rightButtonClicked();
        void okButtonClicked();

        LayoutList *menuList;

        String MAIN_MENU[3][2] = 
        {
            {"Status", "STATUS"},
            {"Reset", "RESET"},
            {"Back", "BACK"},
        };

        String RESET_MENU[4][2] = 
        {
            {"Reset tickers", "RESET_TICKERS"},
            {"Reset settings", "RESET_SETTINGS"}, 
            {"Factory reset", "RESET_FACTORY"},
            {"Back", "RESET_BACK"}    
        };
};

#endif