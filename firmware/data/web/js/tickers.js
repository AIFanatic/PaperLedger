$(document).ready(function() {
    const CONTENT_TICKERS = ".main > .content > .tickers";
    const SUBCONTENT_TICKERS = CONTENT_TICKERS + " > .sub-content";
    const INPUT_TICKERS_COIN = ".tickers .input-coin";
    const INPUT_TICKERS_CURRENCY = ".tickers .input-currency";

    const LIST_TICKERS_COINS = $(INPUT_TICKERS_COIN).immybox({choices: [], showArrow: false, maxResults: 100});
    const LIST_TICKERS_CURRENCIES = $(INPUT_TICKERS_CURRENCY).immybox({choices: [], showArrow: false, maxResults: 100});

    const BTN_TICKER_ADD = ".btn-ticker-add";
    const BTN_TICKER_REMOVE = ".btn-ticker-remove";
    const BTN_ALARMS = ".btn-alarms";
    const BTN_ALARMS_ADD = ".btn-alarms-add";
    const BTN_ALARMS_REMOVE = ".btn-alarms-remove";
    const BTN_ALARMS_TYPE = ".btn-alarms-type";

    function getTickers() {
        if(LIST_TICKERS_COINS[0].options.choices.length == 0) {
            console.log("loaded")
            $.getJSON(ENDPOINT_TICKERS + "/coins/list", (response) => {
                var choices = [];
                for(coin of response) {
                    choices.push({text: coin["name"], value: coin["id"]});
                }
                LIST_TICKERS_COINS[0].setChoices(choices);
            });
        }

        if(LIST_TICKERS_CURRENCIES[0].options.choices.length == 0) {
            $.getJSON(ENDPOINT_TICKERS + "/simple/supported_vs_currencies", (response) => {
                var choices = [];
                for(currency of response) {
                    choices.push({text: currency.toUpperCase(), value: currency.toUpperCase()});
                }
                LIST_TICKERS_CURRENCIES[0].setChoices(choices);
            });
        }
    }

    function showTickers() {
        $(SUBCONTENT_TICKERS).html("");

        $.getJSON(ENDPOINT_URL + "/data/tickers/list", (response) => {
            if(response["status"] == "ok") {
                const tickers = response["message"];

                for(ticker of tickers) {
                    var newBox = $('<div class="box"></div>');
                    newBox.text(ticker["coin"] + " - " + ticker["currency"]);
                    newBox.attr("data-id", ticker["id"]);
                    newBox.attr("data-coin", ticker["coin"]);
                    newBox.attr("data-currency", ticker["currency"]);

                    var deleteButton = $('<a class="button dark-blue red-bg btn-ticker-remove" href="#"><i class="fas fa-trash"></i></a>');
                    var alarmsButton = $('<a class="button dark-blue yellow-bg btn-alarms" href="#"><i class="fas fa-clock"></i></a>');

                    newBox.append(deleteButton);
                    newBox.append(alarmsButton);

                    // Alarms
                    const alarms = ticker["alarms"];
                    var alarmCount = 0;
                    for(alarm of alarms) {
                        var typeIcon = '<i class="fas fa-caret-up green"></i>';
                        if(alarm["type"] == 1) {
                            typeIcon = '<i class="fas fa-caret-down red"></i>';
                        }

                        var alarmBox = $('<div class="alarms-box"></div>');
                        alarmBox.append(typeIcon);
                        alarmBox.append(" <input disabled value='$" + alarm["price"] + "'>");
                        alarmBox.append("<input disabled value='" + alarm["duration"] + "s'>");
                        alarmBox.append("<input disabled value='" + alarm["frequency"] + "Hz'>");
                        alarmBox.append("<input disabled value='#" + alarm["beeps"] + "'>");
                        alarmBox.attr("data-index", alarmCount);

                        var alarmDeleteButton = $('<a class="button dark-blue red-bg btn-alarms-remove" href="#"><i class="fas fa-trash"></i></a>');
                        
                        alarmBox.append(alarmDeleteButton);
                        newBox.append(alarmBox);

                        alarmCount++;
                    }

                    // Add new alarm box
                    var newAlarmBox = $('<div class="alarms-box"></div>');
                    newAlarmBox.append( $('<a class="green btn-alarms-type" data-type="0" href="#"><i class="fas fa-caret-up"></i></a>') );
                    newAlarmBox.append( $('<input class="input-price" type="number" placeholder="Price" min=0>') );
                    newAlarmBox.append( $('<input class="input-duration" type="number" placeholder="Duration">') );
                    newAlarmBox.append( $('<input class="input-frequency" type="number" placeholder="Freq">') );
                    newAlarmBox.append( $('<input class="input-beeps" type="number" placeholder="Beeps">') );
                    newAlarmBox.append( $('<a class="button dark-blue green-bg btn-alarms-add" href="#"><i class="fas fa-plus"></i></a>') );

                    newBox.append(newAlarmBox);

                    $(SUBCONTENT_TICKERS).append(newBox);
                }

                $(HEADER_TITLE_RIGHT).html('You have ' + tickers.length + " ticker(s)");
            }
        });
    }

    $(document).on("click", BTN_TICKER_REMOVE, function() {
        const parent = $(this).parent(".box");
        const id = parent.attr("data-id");
        const currency = parent.attr("data-currency");

        $.post(ENDPOINT_URL + "/data/tickers/remove", {id: id, currency: currency}, (response) => {
            showTickers();
        });
    });

    $(document).on("click", BTN_TICKER_ADD, function() {
        if(LIST_TICKERS_COINS[0].selectedChoice === null || LIST_TICKERS_CURRENCIES[0].selectedChoice === null) {
            alert("Please select a coin and currency");
            return;
        }

        const id = LIST_TICKERS_COINS[0].selectedChoice.value;
        const coin = LIST_TICKERS_COINS[0].selectedChoice.text;
        const currency = LIST_TICKERS_CURRENCIES[0].selectedChoice.value

        $.post(ENDPOINT_URL + "/data/tickers/add", {id: id, coin: coin, currency: currency}, (response) => {
            $(INPUT_TICKERS_COIN).val("");
            $(INPUT_TICKERS_CURRENCY).val("");
            showTickers();
        });
    });

    $(document).on("click", BTN_ALARMS_TYPE, function(e) {
        e.preventDefault();
        const type = $(this).attr("data-type");
        if(type == 0) {
            $(this).removeClass("green");
            $(this).addClass("red");
            $(this).html('<i class="fas fa-caret-down"></i>')
            $(this).attr("data-type", "1");
        }
        else if(type == 1) {
            $(this).removeClass("red");
            $(this).addClass("green");
            $(this).html('<i class="fas fa-caret-up"></i>')
            $(this).attr("data-type", "0");
        }
    });

    $(document).on("click", BTN_ALARMS, function() {
        const parent = $(this).parent(".box");

        if(parent.css("height") != "60px") {
            parent.css("height", "60px");
            return;
        }

        parent.css("height", "initial");
    });

    $(document).on("click", BTN_ALARMS_REMOVE, function() {
        const parentAlarmsBox = $(this).parent(".alarms-box");
        const parentBox = parentAlarmsBox.parent(".box");
        
        const id = parentBox.attr("data-id");
        const currency = parentBox.attr("data-currency");
        const index = parentAlarmsBox.attr("data-index");

        $.post(ENDPOINT_URL + "/data/alarms/remove", {id: id, currency: currency, index: index}, (response) => {
            showTickers();
        });
    });

    $(document).on("click", BTN_ALARMS_ADD, function() {
        const parentAlarmsBox = $(this).parent(".alarms-box");
        const parentBox = parentAlarmsBox.parent(".box");

        const id = parentBox.attr("data-id");
        const currency = parentBox.attr("data-currency");
        const price = $(this).siblings(".input-price").val();
        const duration = $(this).siblings(".input-duration").val();
        const frequency = $(this).siblings(".input-frequency").val();
        const beeps = $(this).siblings(".input-beeps").val();
        const type = $(this).siblings(BTN_ALARMS_TYPE).attr("data-type");

        if(isNaN(price) || isNaN(duration) || isNaN(frequency) || isNaN(beeps) || price == 0 || duration == 0 || frequency == 0 || beeps == 0) {
            alert("Please enter valid positive values, all fields need to be filled.");
            return;
        }

        $.post(ENDPOINT_URL + "/data/alarms/add", 
        {
            id: id, 
            currency: currency, 
            price: price, 
            duration: duration, 
            type: type, 
            frequency: frequency, 
            beeps: beeps
        }, (response) => {
            showTickers();
        });
    });

    document.addEventListener('MENU_CHANGED', (event) => {
        if(event.detail.menu == "tickers") {
            $(HEADER_TITLE).html("Tickers");
            $(HEADER_TITLE_RIGHT).html('Getting data <i class="fas fa-circle-notch fa-spin"></i>');

            getTickers();
            showTickers();
        }
    });

    $(SUBCONTENT_TICKERS).sortable({
        items: ".box:not(.non-sortable)",
        start: function(event, ui) {
            $(this).attr('data-previndex', ui.item.index());
        },
        update: function(event, ui) {
            var from = $(this).attr('data-previndex');
            var to = ui.item.index();

            $(this).removeAttr('data-previndex');

            $.post(ENDPOINT_URL + "/data/tickers/order", {from: from, to: to}, (response) => {
                console.log(response);
            });
        }
    });

    $(".tickers" ).disableSelection();
});