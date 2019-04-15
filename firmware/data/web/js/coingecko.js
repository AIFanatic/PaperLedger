export const getCoins = () => {
    return $.ajax({ url: "https://api.coingecko.com/api/v3/coins/list", dataType: 'json' }).then((response) => {
        const choices = [];
        response.forEach(coin => {
            choices.push({ text: coin["name"], value: coin["id"] });
        });

        return choices;
    });
}

export const getCurrencies = () => {
    return $.ajax({ url: "https://api.coingecko.com/api/v3/simple/supported_vs_currencies", dataType: 'json' }).then((response) => {
        const choices = [];
        response.forEach(currency => {
            choices.push({ text: currency.toUpperCase(), value: currency.toUpperCase() });
        });

        return choices;
    });
}