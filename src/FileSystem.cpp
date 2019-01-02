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

void FileSystem::listDir(fs::FS &fs, const char * dirname, uint8_t levels) {
    Serial.printf("Listing directory: %s\r\n", dirname);

    File root = fs.open(dirname);
    if(!root){
        Serial.println("- failed to open directory");
        return;
    }
    if(!root.isDirectory()){
        Serial.println(" - not a directory");
        return;
    }

    File file = root.openNextFile();
    while(file){
        if(file.isDirectory()){
            Serial.print("  DIR : ");
            Serial.println(file.name());
            if(levels){
                listDir(fs, file.name(), levels -1);
            }
        } else {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("\tSIZE: ");
            Serial.println(file.size());
        }
        file = root.openNextFile();
    }
}

bool FileSystem::readFile(fs::FS &fs, const char *filename, File &file) {
    file = fs.open(filename);
    if (!file) {
        return false;
    }

    return true;
};

void FileSystem::printFile(fs::FS &fs, const char * path) {
    Serial.printf("Reading file: %s\r\n", path);

    File file = fs.open(path);
    if(!file || file.isDirectory()){
        Serial.println(F("Failed to read file"));
    }

    while(file.available()){
        Serial.write(file.read());
    }
}

bool FileSystem::writeFile(fs::FS &fs, const char * path, const char * message) {
    File file = fs.open(path, FILE_WRITE);
    if(!file){
        return false;
    }
    if(file.print(message)){
        return true;
    }
    
    return false;
}

bool FileSystem::appendFile(fs::FS &fs, const char * path, const char * message) {
    File file = fs.open(path, FILE_APPEND);
    
    if(!file){
        return false;
    }

    if(file.print(message)){
        return true;
    }
    
    return false;
}

bool FileSystem::renameFile(fs::FS &fs, const char * path1, const char * path2) {
    if (fs.rename(path1, path2)) {
        return true;
    }

    return false;
}

bool FileSystem::deleteFile(fs::FS &fs, const char * path) {
    if(fs.remove(path)){
        return true;
    }
    
    return false;
}