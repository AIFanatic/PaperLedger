export const getCoins = () => {
    return $.ajax({ url: "https://apiv2.bitcoinaverage.com/symbols/indices/ticker", dataType: 'json' }).then((response) => {
        const coins = new Set();
        response['local']['symbols'].forEach((item) => {
            coins.add(item.substring(0, 3));
        });

        const choices = [];
        coins.forEach((coin) => choices.push({ text: coin.toUpperCase(), value: coin.toUpperCase() }));

        return choices;
    });
}

export const getCurrencies = () => {
    return $.ajax({ url: "https://apiv2.bitcoinaverage.com/symbols/indices/ticker", dataType: 'json' }).then((response) => {
        const currencies = new Set();
        response['local']['symbols'].forEach((item) => {
            currencies.add(item.substring(3, 6));
        });

        const choices = [];
        currencies.forEach((currency) => choices.push({ text: currency.toUpperCase(), value: currency.toUpperCase() }));

        return choices;
    });
}