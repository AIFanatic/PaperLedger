#include "Updater.h"

#include "Manager.h"

Updater::Updater(Manager *_manager) {
    manager = _manager;
};

Updater::~Updater() {
};

void Updater::list() {
    esp_partition_iterator_t it;
    esp_partition_t *pPart;
    it = esp_partition_find(ESP_PARTITION_TYPE_APP, ESP_PARTITION_SUBTYPE_ANY, nullptr);
    
    while (it != nullptr)
    {
        pPart = (esp_partition_t *) esp_partition_get(it);
        printf("main: partition type = %d.\n", pPart->type);
        printf("main: partition subtype = %d.\n", pPart->subtype);
        printf("main: partition starting address = %x.\n", pPart->address);
        printf("main: partition size = %x.\n", pPart->size);
        printf("main: partition label = %s.\n", pPart->label);
        printf("main: partition subtype = %d.\n", pPart->encrypted);
        printf("\n");
        it = esp_partition_next(it);
    }

    it = esp_partition_find(ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_ANY, nullptr);
    while (it != nullptr)
    {
        pPart = (esp_partition_t *) esp_partition_get(it);
        printf("main: partition type = %d.\n", pPart->type);
        printf("main: partition subtype = %d.\n", pPart->subtype);
        printf("main: partition starting address = %x.\n", pPart->address);
        printf("main: partition size = %x.\n", pPart->size);
        printf("main: partition label = %s.\n", pPart->label);
        printf("main: partition subtype = %d.\n", pPart->encrypted);
        printf("\n");
        it = esp_partition_next(it);
    }
    esp_partition_iterator_release(it);
}