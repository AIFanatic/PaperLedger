#include "Speaker.h"

#include "../Manager.h"

Speaker::Speaker(Manager *_manager) {
    manager = _manager;

    // pinMode(SPEAKER_PIN, INPUT_PULLDOWN);
}

void Speaker::start() {
    ledcSetup(TONE_PIN_CHANNEL, 0, 8);
    ledcAttachPin(SPEAKER_PIN, TONE_PIN_CHANNEL);
}

void Speaker::end() {
    ledcDetachPin(SPEAKER_PIN);
}

void Speaker::tone(uint16_t frequency) {
    ledcWriteTone(TONE_PIN_CHANNEL, frequency);
}

void Speaker::beep(uint16_t frequency, uint16_t duration, uint16_t numBeeps) {
    start();

    for(int i = 0; i < numBeeps; i++) {
        tone(frequency);
        delay(duration / 2);
        mute();
        delay(duration / 2);

    }

    end();
}

void Speaker::mute() {
    ledcWriteTone(TONE_PIN_CHANNEL, 0);
    digitalWrite(SPEAKER_PIN, 0);
}

void Speaker::update() {
    if(manager->deepSleep->isGoingToDeepSleep()) {
        // pinMode(SPEAKER_PIN, OUTPUT);
    }
}