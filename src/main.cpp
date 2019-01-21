#include "./layout/Manager.h"

Manager *manager;

void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);
   
    manager = new Manager();
    manager->show(LAYOUT_MAIN);
}

void loop() {
    manager->update();
}