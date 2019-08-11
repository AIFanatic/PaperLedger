#ifndef _SPEAKER_H_
#define _SPEAKER_H_

#include "Arduino.h"

#include "../../variables.h"

class Manager;

class Speaker {
public:
    Speaker(Manager *_manager);
    
    void mute();
    void tone(uint16_t frequency);
    void beep(uint16_t frequency, uint16_t duration, uint16_t numBeeps);
    void update();
    
private:
    Manager *manager;
    
    void start();
    void end();

    int TONE_PIN_CHANNEL = 0;
};

#endif