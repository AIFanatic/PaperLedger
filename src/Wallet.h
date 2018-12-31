#ifndef WALLET_H
#define WALLET_H

#include "./FileSystem.h"

#include <ArduinoJson.h>

#define WALLET_FILENAME "/wallet.json"
#define BALANCE_FILENAME "/balance.json"

class Wallet {
    public:
        Wallet(FileSystem *_filesystem);
        ~Wallet(void);

        JsonVariant getBalances();

    private:
        JsonVariant openJSONFile(const char *filename);
        
        FileSystem *filesystem;

        JsonVariant walletJson;
        JsonVariant balanceJson;
};

#endif