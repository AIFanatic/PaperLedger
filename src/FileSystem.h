#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "SD.h"
#include "board.h"

class FileSystem {
    public:
        FileSystem();
        ~FileSystem(void);

        void getFile(const char *filename, File &file);

    private:

        bool isInitialised;
};

#endif