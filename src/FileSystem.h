#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "SD.h"
#include <SPIFFS.h>
#include "board.h"

class FileSystem {
    public:
        FileSystem();
        ~FileSystem(void);

        void getFileSD(const char *filename, File &file);
        void getFileSPIFFS(const char *filename, File &file);

    private:

        bool isSDInitialised;
        bool isSPIFFSInitialised;
};

#endif