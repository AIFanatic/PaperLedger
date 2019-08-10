#include "Speaker.h"

SPEAKER::SPEAKER(void) {
}

void SPEAKER::start() {
    ledcSetup(TONE_PIN_CHANNEL, 0, 8);
    ledcAttachPin(SPEAKER_PIN, TONE_PIN_CHANNEL);
}

void SPEAKER::end() {
    ledcDetachPin(SPEAKER_PIN);
}

void SPEAKER::tone(uint16_t frequency) {
    ledcWriteTone(TONE_PIN_CHANNEL, frequency);
}

void SPEAKER::beep(uint16_t frequency, uint16_t duration, uint16_t numBeeps) {
    start();

    for(int i = 0; i < numBeeps; i++) {
        tone(frequency);
        delay(duration / 2);
        mute();
        delay(duration / 2);

    }

    end();
}

void SPEAKER::mute() {
    ledcWriteTone(TONE_PIN_CHANNEL, 0);
    digitalWrite(SPEAKER_PIN, 0);
}

void SPEAKER::update() {
}