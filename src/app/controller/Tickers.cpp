#include "Tickers.h"

#include "../Manager.h"

Tickers::Tickers(Manager *_manager) {
    manager = _manager;

    bool tickersFileExists = manager->filesystem->exists(SPIFFS, FILE_TICKERS);

    if(!tickersFileExists) {
        Serial.print("Tickers.json is not valid, creating...");

        manager->filesystem->writeFile(SPIFFS, FILE_TICKERS, "[]");
    }
};

Tickers::~Tickers() {
};

String Tickers::get() {
    File tickersFile;
    manager->filesystem->readFile(SPIFFS, FILE_TICKERS, tickersFile);

    String contents = tickersFile.readString();

    tickersFile.close();

    return contents;
}

bool Tickers::add(const char *id, const char *coin, const char *currency) {
    File tickersFile;
    DynamicJsonBuffer jsonBuffer;

    manager->filesystem->readFile(SPIFFS, FILE_TICKERS, tickersFile);
    JsonArray& tickersArray = jsonBuffer.parse(tickersFile);

    tickersFile.close();

    DynamicJsonBuffer objBuffer;
    JsonObject& obj = objBuffer.createObject();

    DynamicJsonBuffer alarmsBuffer;
    JsonArray& alarms = alarmsBuffer.createArray();

    obj["id"] = id;
    obj["coin"] = coin;
    obj["currency"] = currency;
    obj["price"] = "0";
    obj["last_update"] = "0";
    obj["change_24h"] = "0";
    obj["vol_24h"] = "0";
    obj["alarms"] = alarms;

    tickersArray.add(obj);

    String str;
    tickersArray.printTo(str);
    
    return manager->filesystem->writeFile(SPIFFS, FILE_TICKERS, str.c_str());
}

int Tickers::getIndexOf(const char *id, const char *currency) {
    File tickersFile;
    DynamicJsonBuffer jsonBuffer;

    manager->filesystem->readFile(SPIFFS, FILE_TICKERS, tickersFile);
    JsonArray& tickersArray = jsonBuffer.parse(tickersFile);
    
    tickersFile.close();

    for(int i = 0; i < tickersArray.size(); i++) {
        String str = tickersArray[i];
        DynamicJsonBuffer objBuffer;
        JsonObject& obj = objBuffer.parse(str);

        if(strcmp(obj["id"], id) == 0 && strcmp(obj["currency"], currency) == 0) {
            return i;
        }
    }

    return -1;
}

bool Tickers::remove(const char *id, const char *currency) {
    int index = getIndexOf(id, currency);

    if(index == -1) {
        return false;
    }

    return remove(index);
}

bool Tickers::remove(int index) {
    File tickersFile;
    DynamicJsonBuffer jsonBuffer;

    manager->filesystem->readFile(SPIFFS, FILE_TICKERS, tickersFile);
    JsonArray& tickersArray = jsonBuffer.parse(tickersFile);

    tickersFile.close();

    tickersArray.remove(index);

    String str;
    tickersArray.printTo(str);
    return manager->filesystem->writeFile(SPIFFS, FILE_TICKERS, str.c_str());
}

void Tickers::reset() {
    manager->filesystem->deleteFile(SPIFFS, FILE_TICKERS);
    manager->filesystem->writeFile(SPIFFS, FILE_TICKERS, "[]");
}

String Tickers::getTickerData(const char *ids, const char *currencies) {
    String url = URL_TICKER_DATA;
    url.concat("&ids=");
    url.concat(ids);
    url.concat("&vs_currencies=");
    url.concat(currencies);

    return manager->webserver->get(url);
}

bool Tickers::updateTickers() {
    Serial.println("Updating tickers");

    File tickersFile;
    DynamicJsonBuffer jsonBuffer;

    manager->filesystem->readFile(SPIFFS, FILE_TICKERS, tickersFile);
    JsonArray& tickersArray = jsonBuffer.parse(tickersFile);

    tickersFile.close();

    String coins;
    String currencies;

    for(int i = 0; i < tickersArray.size(); i++) {
        JsonObject& obj = tickersArray[i].as<JsonObject>();

        String id = obj["id"];
        String currency = obj["currency"];

        coins += id + ",";
        currencies += currency + ",";
    }

    String response = getTickerData(coins.c_str(), currencies.c_str());

    DynamicJsonBuffer responseJsonBuffer;
    JsonObject& responseJson = responseJsonBuffer.parse(response);

    for(int i = 0; i < tickersArray.size(); i++) {
        JsonObject& obj = tickersArray[i].as<JsonObject>();

        String id = obj["id"];
        String currency = obj["currency"];

        // CoinGecko responses are in lowercase
        id.toLowerCase();
        currency.toLowerCase();

        String price = responseJson[id][currency];
        String last_update = responseJson[id]["last_updated_at"];
        String change_24h = String(Utils::roundDecimals(responseJson[id][currency + "_24h_change"], 2));
        String vol_24h = Utils::numToHuman(responseJson[id][currency + "_24h_vol"], 2);

        tickersArray[i]["price"] = price;
        tickersArray[i]["last_update"] = last_update;
        tickersArray[i]["change_24h"] = change_24h;
        tickersArray[i]["vol_24h"] = vol_24h;
    }

    String str;
    tickersArray.printTo(str);
    
    return manager->filesystem->writeFile(SPIFFS, FILE_TICKERS, str.c_str());
}

bool Tickers::changeOrder(int from, int to) {
    File tickersFile;
    DynamicJsonBuffer jsonBuffer;

    manager->filesystem->readFile(SPIFFS, FILE_TICKERS, tickersFile);
    JsonArray& tickersArray = jsonBuffer.parse(tickersFile);

    tickersFile.close();

    if(!tickersArray[from].is<JsonObject>() || !tickersArray[to].is<JsonObject>()) {
        return false;
    }

    JsonObject& fromTemp = tickersArray[from].as<JsonObject>();

    tickersArray[from] = tickersArray[to];
    tickersArray[to] = fromTemp;

    String str;
    tickersArray.printTo(str);
    manager->filesystem->writeFile(SPIFFS, FILE_TICKERS, str.c_str());

    return true;
}