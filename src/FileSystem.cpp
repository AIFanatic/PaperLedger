#include "FileSystem.h"

FileSystem::FileSystem() {
    isInitialised = SD.begin(SDCARD_SS);

    if(!isInitialised) {
        Serial.println("SDCard could not be initialised");
    }
};

FileSystem::~FileSystem() {
    SD.end();
};

void FileSystem::getFile(const char *filename, File &file) {
    if(!isInitialised) {
        return;
    }

    file = SD.open(filename);
    if (!file) {
        Serial.println(F("Failed to read file"));
        // return nullptr;
    }

    // // Extract each characters by one by one
    // while (file.available())
    // {
    //     Serial.print((char)file.read());
    // }
};