$(document).ready(function() {
    const CONTENT_SETUP = ".main > .content > .setup";
    const SUBCONTENT_SETUP = CONTENT_SETUP + " > .sub-content";
    
    const BTN_SETTINGS_UPDATE = ".btn-settings-update";
    
    const INPUT_UPDATE_FILE = CONTENT_SETUP + " .input-update-file";

    function showSettings() {
        $(SUBCONTENT_SETUP).html("");

        $.getJSON(ENDPOINT_URL + "/data/settings/list", (response) => {
            if(response["status"] == "ok") {
                const settings = response["message"];

                console.log(settings)

                for (var key in settings) {
                    if (settings.hasOwnProperty(key)) {
                        var settingParsed = key.replace(/_/g, " ");
                        settingParsed = settingParsed.charAt(0).toUpperCase() + settingParsed.slice(1);

                        var settingValue = settings[key];
                        var newBox = $('<div class="box"></div>');
                        if (settingValue != "true" && settingValue != "false") {
                            settingValue = settingValue + "s";
                        }

                        newBox.text(settingParsed + ": " + settingValue);
                        
                        var button = $('<a class="button dark-blue yellow-bg btn-settings-update" href="#"><i class="fas fa-edit"></i></a>');
                        button.attr("data-name", key);
                        button.attr("data-value", settingValue);

                        newBox.append(button);

                        $(SUBCONTENT_SETUP).append(newBox);
                    }
                }

                $(HEADER_TITLE_RIGHT).html("");
            }
        });
    }

    $(document).on("click", BTN_SETTINGS_UPDATE, function() {
        const name = $(this).attr("data-name");
        const value = $(this).attr("data-value");

        var newValue = prompt("Please enter the new value", value);
        if(newValue == null || newValue === 0) {
            alert("Invalid value entered");
            return;
        }

        $.post(ENDPOINT_URL + "/data/settings/change", {name: name, value: newValue}, (response) => {
            showSettings();
        });
    });

    $(document).on("change", INPUT_UPDATE_FILE, function() {

        $(HEADER_TITLE_RIGHT).html('Updating: <span>0</span>% <i class="fas fa-circle-notch fa-spin"></i>');

        var headerPercentage = $(HEADER_TITLE_RIGHT).children("span");

        const file = $(this).get(0).files[0], formData = new FormData();

        formData.append('file', file);

        $(this).val("");

        $.ajax({
            url: ENDPOINT_URL + "/update",
            type: 'POST',
            contentType: false,
            cache: false,
            processData: false,
            data: formData,
            xhr: function () {
                var jqXHR = null;
                if ( window.ActiveXObject ) {
                    jqXHR = new window.ActiveXObject( "Microsoft.XMLHTTP" );
                }
                else {
                    jqXHR = new window.XMLHttpRequest();
                }
                //Upload progress
                jqXHR.upload.addEventListener("progress", function(evt) {
                    if (evt.lengthComputable) {
                        var percentComplete = Math.round((evt.loaded * 100) / evt.total);
                        $(headerPercentage).text(percentComplete);
                    }
                }, false );
                return jqXHR;
            },
            success: function(data) {
                if(data["status"] == "ok") {
                    $(HEADER_TITLE_RIGHT).html("Updated successfully");
                    return;
                }
                $(HEADER_TITLE_RIGHT).html("Update failed: " + data["message"]);
            },
            error: function(data) {
                $(HEADER_TITLE_RIGHT).html("Update failed: " + data);
            }
        });
    });

    document.addEventListener('MENU_CHANGED', (event) => {
        if(event.detail.menu == "setup") {
            $(HEADER_TITLE).html("Setup");
            $(HEADER_TITLE_RIGHT).html('Getting data <i class="fas fa-circle-notch fa-spin"></i>');
            showSettings();
        }
    });
});