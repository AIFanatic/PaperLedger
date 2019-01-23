$(document).ready(function() {
    document.addEventListener('MENU_CHANGED', (event) => {
        if(event.detail.menu == "dashboard") {
            $(HEADER_TITLE).html("Dashboard");
            $(HEADER_TITLE_RIGHT).html('');
        }
    });

    $.getJSON(ENDPOINT_URL + "/data/wifi/status", (response) => {
        if(response["status"] == "ok") {
            const message = response["message"];
            if(message["internet"] == false) {
                console.log(message["internet"] == false)
                $(SUBCONTENT_DASHBOARD).slideDown();
                return;
            }
    
            $( ".nav-button" ).removeClass("disabled");
        }
    });
});