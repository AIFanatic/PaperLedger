const ENDPOINT_TICKERS = "https://api.coingecko.com/api/v3";

const MAIN = ".main";

const HEADER_TITLE = ".main > .header > .title";
const HEADER_TITLE_RIGHT = ".main > .header > .right";

const PROVIDERS = {
    0: "coingecko",
    1: "bitcoinaverage"
}

const EVENTS = {
    MENU_CHANGED: new CustomEvent("MENU_CHANGED",
        {
            'detail': {
                menu: null
            }
        }
    )
}