#ifndef Updater_h
#define Updater_h

#include <Arduino.h>

#include <esp_partition.h>

class Manager;

class Updater {
    public:
        Updater(Manager *_manager);
        ~Updater(void);

        void list();

    private:
        Manager *manager;
        
};

#endif