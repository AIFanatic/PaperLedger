#include "./app/Manager.h"

Manager *manager;

void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);
   
    manager = new Manager();
    manager->show(VIEW_MAIN);
}

void loop() {
    manager->update();
}