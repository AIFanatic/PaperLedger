#include "Updater.h"

#include "../Manager.h"
#include "../views/UpdateView.h"

Updater::Updater(Manager *_manager) {
    manager = _manager;
};

Updater::~Updater() {
};

const char * Updater::_err2str(uint8_t _error) {
    if(_error == UPDATE_ERROR_OK){
        return ("No Error");
    } else if(_error == UPDATE_ERROR_WRITE){
        return ("Flash Write Failed");
    } else if(_error == UPDATE_ERROR_ERASE){
        return ("Flash Erase Failed");
    } else if(_error == UPDATE_ERROR_READ){
        return ("Flash Read Failed");
    } else if(_error == UPDATE_ERROR_SPACE){
        return ("Not Enough Space");
    } else if(_error == UPDATE_ERROR_SIZE){
        return ("Bad Size Given");
    } else if(_error == UPDATE_ERROR_STREAM){
        return ("Stream Read Timeout");
    } else if(_error == UPDATE_ERROR_MD5){
        return ("MD5 Check Failed");
    } else if(_error == UPDATE_ERROR_MAGIC_BYTE){
        return ("Wrong Magic Byte");
    } else if(_error == UPDATE_ERROR_ACTIVATE){
        return ("Could Not Activate The Firmware");
    } else if(_error == UPDATE_ERROR_NO_PARTITION){
        return ("Partition Could Not be Found");
    } else if(_error == UPDATE_ERROR_BAD_ARGUMENT){
        return ("Bad Argument");
    } else if(_error == UPDATE_ERROR_ABORT){
        return ("Aborted");
    }
    return ("UNKNOWN");
}

void Updater::requestUpdate(AsyncWebServerRequest *request) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& response = jsonBuffer.createObject();

    if(Update.hasError()) {
        response["status"] = "error";
        response["message"] =_err2str(Update.getError());
    }
    else {
        response["status"] = "ok";
        response["message"] = "Updated";
    }

    String str;
    response.printTo(str);
    request->send(200, "application/json", str);
}

void Updater::requestUpdateUpload(AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final) {
    if(!index){ // if index == 0 then this is the first frame of data
        manager->show(UPDATE_VIEW);
        updateView = (UpdateView *) manager->getCurrentView();

        Serial.printf("UploadStart: %s\n", filename.c_str());
        Serial.setDebugOutput(true);
        
        int command = U_FLASH;
        if(filename.equals("spiffs.bin")) {
            command = U_SPIFFS;
            SPIFFS.end();
        }

        // calculate sketch space required for the update
        // uint32_t maxSketchSpace = (ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000;
        if(!Update.begin(UPDATE_SIZE_UNKNOWN, command)) {//start with max available size
            Update.printError(Serial);
        }
        // Update.runAsync(true); // tell the updaterClass to run in async mode
    }

    //Write chunked data to the free sketch space
    if(Update.write(data, len) != len){
        Update.printError(Serial);
    }
    
    if(final) { // if the final flag is set then this is the last frame of data
        if(Update.end(true)) { //true to set the size to the current progress
            Serial.printf("Update Success: %u B\nRebooting...\n", index+len);
            String title = "Updated " + filename;
            updateView->setText("Update completed", title.c_str(), "Please restart your device");
        } else {
            Update.printError(Serial);
            updateView->setText("Update failed", _err2str(Update.getError()), "Please restart your device");
        }
        Serial.setDebugOutput(false);
    }
}