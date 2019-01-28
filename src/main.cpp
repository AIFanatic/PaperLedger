#include "./app/Manager.h"

Manager *manager;

void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);
   
    manager = new Manager();
    manager->show(LOADING_VIEW);
}

void loop() {
    manager->update();
}