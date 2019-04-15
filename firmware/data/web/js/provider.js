class Provider {
    constructor() {
        this.storage = window.localStorage;
    }

    get() {
        if (false === this.storage.getItem("connected")) {
            return [];
        }

        let settings = JSON.parse(this.storage.getItem("settings"));
        if (settings == null || typeof settings === "undefined") {
            return [];
        }

        return import('./' + PROVIDERS[settings.data_source] + '.js');
    }
}