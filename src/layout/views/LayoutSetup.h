#ifndef LayoutSetup_H
#define LayoutSetup_H

#include "../Render.h"
#include "../Display.h"
#include "../helpers/LayoutBase.h"
#include "../helpers/LayoutList.h"

#include <MenuBackend.h>

#define SIZEOFARRAY(x)  (sizeof(x) / sizeof((x)[0]))

class LayoutSetup: public LayoutBase {
    public:
        LayoutSetup(Display *_display);
        ~LayoutSetup(void);

    private:        
        void initMenu();
        void showMenu(const char *menu[], int size);

        void leftButtonClicked();
        void rightButtonClicked();
        void okButtonClicked();

        static void menuChangeEventStatic(MenuChangeEvent changed, void *context);
        void menuChangeEvent(MenuChangeEvent changed);

        static void menuUseEventStatic(MenuUseEvent changed, void *context);
        void menuUseEvent(MenuUseEvent changed);

        LayoutList *menuList;

        MenuBackend *menuRoot;

        // MAIN MENU
        MenuItem TICKERS = MenuItem("TICKERS");
            MenuItem ADD_TICKER = MenuItem("ADD_TICKER");
            MenuItem REMOVE_TICKER = MenuItem("REMOVE_TICKER");
            MenuItem BACK_TICKER = MenuItem("BACK_TICKER");

        MenuItem CUSTOMIZE = MenuItem("CUSTOMIZE");
        MenuItem NETWORK = MenuItem("NETWORK");
        MenuItem BACK = MenuItem("BACK");

        const char *MAIN_MENU[4] = {"Tickers", "Customize", "Network", "Back"};        
        const char *TICKERS_MENU[3] = {"Add ticker", "Remove ticker", "Back"};

};

#endif