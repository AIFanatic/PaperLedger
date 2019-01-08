#include "Tickers.h"

#include "Manager.h"

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

JsonArray& Tickers::get() {
    File tickersFile;
    manager->filesystem->readFile(SPIFFS, FILE_TICKERS, tickersFile);

    DynamicJsonBuffer jsonBuffer;
    JsonArray& tickersArray = jsonBuffer.parse(tickersFile);
    tickersFile.close();

    return tickersArray;
}

bool Tickers::add(const char *coin, const char *currency) {
    File tickersFile;
    DynamicJsonBuffer jsonBuffer;

    manager->filesystem->readFile(SPIFFS, FILE_TICKERS, tickersFile);
    JsonArray& tickersArray = jsonBuffer.parse(tickersFile);

    tickersFile.close();

    DynamicJsonBuffer objBuffer;
    JsonObject& obj = objBuffer.createObject();
    obj["coin"] = coin;
    obj["currency"] = currency;
    obj["price"] = "0";
    obj["last_update"] = "0";
    obj["change_24h"] = "0";

    tickersArray.add(obj);

    String str;
    tickersArray.printTo(str);
    manager->filesystem->writeFile(SPIFFS, FILE_TICKERS, str.c_str());
}

int Tickers::getIndexOf(const char *coin, const char *currency) {
    File tickersFile;
    DynamicJsonBuffer jsonBuffer;

    manager->filesystem->readFile(SPIFFS, FILE_TICKERS, tickersFile);
    JsonArray& tickersArray = jsonBuffer.parse(tickersFile);
    
    tickersFile.close();

    for(int i = 0; i < tickersArray.size(); i++) {
        String str = tickersArray[i];
        DynamicJsonBuffer objBuffer;
        JsonObject& obj = objBuffer.parse(str);

        if(strcmp(obj["coin"], coin) == 0 && strcmp(obj["currency"], currency) == 0) {
            return i;
        }
    }

    return -1;
}

bool Tickers::remove(const char *coin, const char *currency) {
    int index = getIndexOf(coin, currency);

    if(index == -1) {
        return false;
    }

    remove(index);

    return true;
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
    manager->filesystem->writeFile(SPIFFS, FILE_TICKERS, str.c_str());

    return true;
}

void Tickers::reset() {
    manager->filesystem->deleteFile(SPIFFS, FILE_TICKERS);
    manager->filesystem->writeFile(SPIFFS, FILE_TICKERS, "[]");
}

String Tickers::getTickerData(const char *coins, const char *currencies) {
    String url = URL_TICKER_DATA;
    url.concat("&ids=");
    url.concat(coins);
    url.concat("&vs_currencies=");
    url.concat(currencies);

    return manager->networkManager->get(url);
}

bool Tickers::updateTickers() {
    Serial.println("Updating tickers");

    File tickersFile;
    DynamicJsonBuffer jsonBuffer;

    manager->filesystem->readFile(SPIFFS, FILE_TICKERS, tickersFile);
    JsonArray& tickersArray = jsonBuffer.parse(tickersFile);

    tickersFile.close();

    for(int i = 0; i < tickersArray.size(); i++) {
        String str = tickersArray[i];
        DynamicJsonBuffer objBuffer;
        JsonObject& obj = objBuffer.parse(str);

        String coin = obj["coin"];
        String currency = obj["currency"];

        String response = getTickerData(coin.c_str(), currency.c_str());

        DynamicJsonBuffer responseJsonBuffer;
        JsonObject& responseJson = responseJsonBuffer.parse(response);

        // CoinGecko responses are in lowercase
        coin.toLowerCase();
        currency.toLowerCase();

        String price = responseJson[coin][currency];
        String last_update = responseJson[coin]["last_updated_at"];
        String change_24h = responseJson[coin][currency + "_24h_change"];

        tickersArray[i]["price"] = price;
        tickersArray[i]["last_update"] = last_update;
        tickersArray[i]["change_24h"] = change_24h;
    }

    String str;
    tickersArray.printTo(str);
    manager->filesystem->writeFile(SPIFFS, FILE_TICKERS, str.c_str());
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

    DynamicJsonBuffer tempBuffer;
    String fromTempStr = tickersArray[from];
    JsonObject& fromTemp = tempBuffer.parse(fromTempStr);

    tickersArray[from] = tickersArray[to];
    tickersArray[to] = fromTemp;

    String str;
    tickersArray.printTo(str);
    manager->filesystem->writeFile(SPIFFS, FILE_TICKERS, str.c_str());

    return true;
}