$(document).ready(function() {
    const NAV = ".nav";
    const NAV_BUTTON = ".nav-button";
    const NAV_OPEN_BUTTON = ".nav-open-button";

    var currentMenu = "dashboard";

    function showMenu(menu) {
        if(EVENTS.MENU_CHANGED.detail.menu !== menu) {
            $(".main > .content ." + currentMenu).hide();
            $(".main > .content ." + menu).show();

            currentMenu = menu;

            EVENTS.MENU_CHANGED.detail.menu = menu;
            document.dispatchEvent(EVENTS.MENU_CHANGED);
        }
    }

    $(document).on("click", NAV_BUTTON, function() {
        if(!$(this).hasClass("disabled")) {
            const menu = $(this).attr("data-menu");

            showMenu(menu);

            $(NAV).removeClass("nav-mobile");
            $(MAIN).removeClass("main-filter");
        }
    });

    $(document).on("click", NAV_OPEN_BUTTON, function() {
        $(NAV).toggleClass("nav-mobile");
        $(MAIN).toggleClass("main-filter");
    });
});