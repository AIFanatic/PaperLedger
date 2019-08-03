#ifndef DeepSleep_h
#define DeepSleep_h

#include <Arduino.h>

class Manager;

class DeepSleep {
    public:
        DeepSleep(Manager *_manager);
        ~DeepSleep(void);

        int getWakeupCause();

        bool hasBootedFromDeepSleep();

        bool canEnterDeepSleep();
        void enterDeepSleep();

        void setMinAwakeBootTimeOffset(long offsetMillis);

        void update();

    private:
        Manager *manager;

        long minAwakeBootTime;
};

#endif