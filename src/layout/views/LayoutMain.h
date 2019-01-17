#ifndef LayoutMain_H
#define LayoutMain_H

#include "../Render.h"
#include "../Manager.h"
#include "../helpers/LayoutBase.h"

class LayoutMain: public LayoutBase {
    public:
        LayoutMain(Manager *_manager);
        ~LayoutMain(void);

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