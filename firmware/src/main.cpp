#include "./app/Manager.h"

Manager *manager;

void setup() {
    Serial.begin(115200);
   
    manager = new Manager();
}

void loop() {
    manager->update();
}