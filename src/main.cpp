#include "./layout/Manager.h"

Manager *manager;

void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);
   
    manager = new Manager();
    manager->show(LAYOUT_MAIN);

    // LayoutList *list = new LayoutList(render);
    // list->init(128, 32, 160, 80, 18, BLACK);
    // list->add("Status");
    // list->add("Connect");
    // list->add("Disconnect");
    // list->add("Back");
    // list->draw();

    // delay(5000);
    // list->setActive(list->getActive()+1);
    // delay(5000);
    // list->setActive(list->getActive()+1);

    // File file;
    // manager->filesystem->readFile(SD, "/wallet.json", file);

    // while(file.available()){
    //     Serial.write(file.read());
    // }

    // file.close();
}

void loop() {
    manager->update();
}