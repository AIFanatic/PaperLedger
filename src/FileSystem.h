#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "SD.h"
#include <SPIFFS.h>
#include "board.h"

class FileSystem {
    public:
        FileSystem();
        ~FileSystem(void);

        void listDir(fs::FS &fs, const char * dirname, uint8_t levels);
        bool readFile(fs::FS &fs, const char *filename, File &file);
        void printFile(fs::FS &fs, const char * path);
        bool writeFile(fs::FS &fs, const char * path, const char * message);
        bool appendFile(fs::FS &fs, const char * path, const char * message);
        bool renameFile(fs::FS &fs, const char * path1, const char * path2);
        bool deleteFile(fs::FS &fs, const char * path);
        bool exists(fs::FS &fs, const char * path);
    private:

        bool isSDInitialised;
        bool isSPIFFSInitialised;
};

#endif