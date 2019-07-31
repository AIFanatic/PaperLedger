#ifndef MainView_H
#define MainView_H

#include "../helpers/LayoutBase.h"

class MainView: public LayoutBase {
    public:
        MainView(Manager *_manager);
        ~MainView(void);

    private:
        void leftButtonClicked();
        void rightButtonClicked();
        void okButtonClicked();

        void showMenu();

        enum MENUS {
            WALLET,
            TICKERS,
            SETUP
        };

        int currentMenu = TICKERS;
};

#endif