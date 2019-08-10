#ifndef _SPEAKER_H_
#define _SPEAKER_H_

#include "Arduino.h"

#include "../../variables.h"

class SPEAKER {
public:
    SPEAKER(void);
    
    void mute();
    void tone(uint16_t frequency);
    void beep(uint16_t frequency, uint16_t duration, uint16_t numBeeps);
    void update();
    
private:
    void start();
    void end();

    int TONE_PIN_CHANNEL = 0;
};

#endif