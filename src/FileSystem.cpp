#include "FileSystem.h"

FileSystem::FileSystem() {
    isSDInitialised = SD.begin(SDCARD_SS);

    if(!isSDInitialised) {
        Serial.println("SDCard could not be initialised");
    }

    isSPIFFSInitialised = SPIFFS.begin();

    if(!isSPIFFSInitialised) {
        Serial.println("SPIFFS could not be initialised");
    }
};

FileSystem::~FileSystem() {
    SD.end();
    SPIFFS.end();
};

void FileSystem::getFileSD(const char *filename, File &file) {
    if(!isSDInitialised) {
        return;
    }

    file = SD.open(filename);
    if (!file) {
        Serial.println(F("Failed to read file"));
    }
};

void FileSystem::getFileSPIFFS(const char *filename, File &file) {
    if(!isSPIFFSInitialised) {
        return;
    }

    file = SPIFFS.open(filename);
    if (!file) {
        Serial.println(F("Failed to read file"));
    }
};