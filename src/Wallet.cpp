#include "Wallet.h"

Wallet::Wallet(FileSystem *_filesystem) {
    filesystem = _filesystem;
    
    // Open files
    // walletJson = openJSONFile(WALLET_FILENAME);
    // balanceJson = openJSONFile(BALANCE_FILENAME);
    JsonVariant v = openJSONFile(BALANCE_FILENAME);
    balanceJson = v;
    balanceJson.prettyPrintTo(Serial);
};

Wallet::~Wallet() {
};

// // TODO: Clean
JsonVariant Wallet::openJSONFile(const char *filename) {
    File file;

    filesystem->getFile(filename, file);

    if (!file) {
        Serial.print("Unable to open: ");
        Serial.println(filename);
        return NULL;
    }

    DynamicJsonBuffer jsonBuffer;
    JsonVariant v = jsonBuffer.parse(file);

    file.close();

    String n = v[0]["name"];
    Serial.println(n);

    return v;
}

JsonVariant Wallet::getBalances() {
    balanceJson.prettyPrintTo(Serial);
    return balanceJson;
}