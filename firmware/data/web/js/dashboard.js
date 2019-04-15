$(document).ready(function() {
    const CONTENT_DASHBOARD = ".main > .content > .dashboard";
    const SUBCONTENT_DASHBOARD = CONTENT_DASHBOARD + " > .content .sub-content";

    $.getJSON("/data/wifi/status", (response) => {
        if (response["status"] != "ok") {
            return;
        }

        const message = response["message"];

        const has_internet = message["internet"];
        window.localStorage.setItem("connected", has_internet);

        if (false == has_internet) {
            $(SUBCONTENT_DASHBOARD).slideDown();
            return;
        }

        $(".nav-button").removeClass("disabled");

    });

    $.getJSON("/data/settings/list").then((response) => {
        window.localStorage.setItem("settings", JSON.stringify(response["message"]));
    });
    
    document.addEventListener('MENU_CHANGED', (event) => {
        if (event.detail.menu != "dashboard") {
            return; 
        }

        $(HEADER_TITLE).html("Dashboard");
        $(HEADER_TITLE_RIGHT).html('');
    });
});