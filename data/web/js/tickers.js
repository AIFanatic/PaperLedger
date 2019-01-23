$(document).ready(function() {
    const CONTENT_TICKERS = ".main > .content > .tickers";
    const SUBCONTENT_TICKERS = CONTENT_TICKERS + " > .sub-content";
    const INPUT_TICKERS_COIN = ".tickers .input-coin";
    const INPUT_TICKERS_CURRENCY = ".tickers .input-currency";

    const LIST_TICKERS_COINS = $(INPUT_TICKERS_COIN).immybox({choices: [],showArrow: false});
    const LIST_TICKERS_CURRENCIES = $(INPUT_TICKERS_CURRENCY).immybox({choices: [],showArrow: false});

    const BTN_TICKER_ADD = ".btn-ticker-add";
    const BTN_TICKER_REMOVE = ".btn-ticker-remove";
    const BTN_ALARMS = ".btn-alarms";
    const BTN_ALARMS_ADD = ".btn-alarms-add";
    const BTN_ALARMS_REMOVE = ".btn-alarms-remove";

    function getTickers() {
        if(LIST_TICKERS_COINS[0].options.choices.length == 0) {
            console.log("loaded")
            $.getJSON(ENDPOINT_TICKERS + "/coins/list", (response) => {
                for(coin of response) {
                    LIST_TICKERS_COINS[0].options.choices.push({text: coin["name"], value: coin["id"]});
                }
            });
        }

        if(LIST_TICKERS_CURRENCIES[0].options.choices.length == 0) {
            $.getJSON(ENDPOINT_TICKERS + "/simple/supported_vs_currencies", (response) => {
                for(currency of response) {
                    LIST_TICKERS_CURRENCIES[0].options.choices.push({text: currency.toUpperCase(), value: currency.toUpperCase()});
                }
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
                        var alarmBox = $('<div class="alarms-box">Price: ' + alarm["price"] + " - Duration: " + alarm["duration"] + 's</div>');
                        alarmBox.attr("data-index", alarmCount);

                        var alarmDeleteButton = $('<a class="button dark-blue red-bg btn-alarms-remove" href="#"><i class="fas fa-trash"></i></a>');
                        
                        alarmBox.append(alarmDeleteButton);
                        newBox.append(alarmBox);

                        alarmCount++;
                    }

                    // Add new alarm box
                    var newAlarmBox = $('<div class="alarms-box"></div>');
                    newAlarmBox.append( $('<input class="input-price col-4" type="number" placeholder="Price">') );
                    newAlarmBox.append( $('<input class="input-duration col-4" type="number" placeholder="Duration">') );
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

        console.log(price)
        console.log(duration)

        console.log(isNaN(price))
        console.log(isNaN(duration))

        if(isNaN(price) || isNaN(duration) || price == 0 || duration == 0) {
            alert("Please enter a valid price and duration");
            return;
        }
        // http://192.168.8.108/data/alarms/add?id=bitcoin&currency=USD&price=2000&duration=3
        $.post(ENDPOINT_URL + "/data/alarms/add", {id: id, currency: currency, price: price, duration: duration}, (response) => {
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