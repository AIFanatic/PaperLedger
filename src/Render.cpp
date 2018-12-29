#include "Render.h"

Render::Render() {
    initDisplay();
    // clearScreen();
};

Render::~Render() {
};

void Render::initDisplay() {
    paint = new Paint(image, 0, 0);

    if (epd.Init(lut_full_update) != 0) {
        Serial.print("e-Paper init failed");
        return;
    }

    epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
    epd.DisplayFrame();

    epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
    epd.DisplayFrame();

    if (epd.Init(lut_partial_update) != 0) {
        Serial.print("e-Paper init failed");
        return;
    }
    
    paint->SetRotate(ROTATE_90);
}

void Render::clearScreen() {
    paint->SetWidth(128);
    paint->SetHeight(128);

    paint->Clear(BLACK);
    epd.SetFrameMemory(paint->GetImage(), 0, 0, paint->GetWidth(), paint->GetHeight());
    epd.SetFrameMemory(paint->GetImage(), 0, 128, paint->GetWidth(), paint->GetHeight());
    epd.SetFrameMemory(paint->GetImage(), 0, 256, paint->GetWidth(), paint->GetHeight());
    epd.DisplayFrame();

    paint->Clear(WHITE);
    epd.SetFrameMemory(paint->GetImage(), 0, 0, paint->GetWidth(), paint->GetHeight());
    epd.SetFrameMemory(paint->GetImage(), 0, 128, paint->GetWidth(), paint->GetHeight());
    epd.SetFrameMemory(paint->GetImage(), 0, 256, paint->GetWidth(), paint->GetHeight());
    epd.DisplayFrame();

    clearBuffer();
}

void Render::clearBuffer() {
    epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
    epd.DisplayFrame();

    epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
    epd.DisplayFrame();
}

void Render::drawFromJson(String json) {
    DynamicJsonBuffer jsonBuffer;
    JsonArray& jsonArray = jsonBuffer.parseArray(json);

    for(int i = 0; i < jsonArray.size(); i++) {
        String params = jsonArray[i];
        JsonObject& obj = jsonBuffer.parseObject( params );

        String type = obj["type"];
        int x = obj["x"];
        int y = obj["y"];
        int color = obj["color"];

        bool requireFrameUpdate = false;

        if(type.equals("rectangle")) {
            int w = obj["w"];
            int h = obj["h"];
            drawRectangle(x, y, w, h, color);
            requireFrameUpdate = true;
        }
        else if(type.equals("circle")) {
            int r = obj["r"];
            drawCircle(x, y, r, color);
            requireFrameUpdate = true;
        }
        else if(type.equals("text")) {
            const char *text = obj["text"];
            int size = obj["size"];
            drawText(x, y, text, size, color);
            requireFrameUpdate = true;
        }
        else if(type.equals("image")) {
            int index = obj["index"];
            int w = obj["w"];
            int h = obj["h"];
            drawImage(index, x, y, w, h);
        }
        else if(type.equals("clear")) {
            clearScreen();
        }
        else if(type.equals("clearBuffer")) {
            clearBuffer();
        }

        if(requireFrameUpdate) {
            addImageToFrame(x, y);
        }
    }

    epd.DisplayFrame();
}

void Render::drawRectangle(int x, int y, int w, int h, int color, bool filled) {
    paint->SetWidth(h+8);
    paint->SetHeight(w+8);
    paint->Clear(!color);

    if(filled) {
        paint->DrawFilledRectangle(4, 4, w+4, h+4, color);    
        return;
    }

    paint->DrawRectangle(4, 4, w+4, h+4, color);
}

void Render::drawCircle(int x, int y, int r, int color, bool filled) {
    paint->SetWidth(r*2+8);
    paint->SetHeight(r*2+8);
    paint->Clear(!color);

    if(filled) {
        paint->DrawFilledCircle(r+4, r+4, r, color);    
        return;
    }

    paint->DrawCircle(r+4, r+4, r, color);
}

void Render::drawText(int x, int y, const char *text, int size, int color) {
    sFONT *font = &Font24;

    if(size == 8) { font = &Font8; }
    else if(size == 12) { font = &Font12; }
    else if(size == 16) { font = &Font16; }
    else if(size == 20) { font = &Font20; }
    else if(size == 24) { font = &Font24; }

    int w = strlen(text) * font->Width;
    paint->SetWidth(font->Height);
    paint->SetHeight(w);

    paint->Clear(!color);
    paint->DrawStringAt(0, 2, text, font, color);
}

void Render::drawText(int x, int y, const char *text, int size, int color, int w, int h) {
    sFONT *font = &Font24;

    if(size == 8) { font = &Font8; }
    else if(size == 12) { font = &Font12; }
    else if(size == 16) { font = &Font16; }
    else if(size == 20) { font = &Font20; }
    else if(size == 24) { font = &Font24; }

    paint->SetWidth(h);
    paint->SetHeight(w);

    paint->Clear(!color);
    paint->DrawStringAt(4, 4, text, font, color);
}

void Render::drawImage(int index, int x, int y, int w, int h) {
    if(index < 0 || index >= (sizeof(ICONS)/sizeof(const unsigned char* const))) {
        Serial.println("Invalid image index");
        return;
    }
    epd.SetFrameMemory(ICONS[index], y, x, w, h);
    epd.SetFrameMemory(ICONS[index], y, x, w, h);
}

void Render::addImageToFrame(int x, int y) {
    // Flip coordinates
    epd.SetFrameMemory(paint->GetImage(), y, x, paint->GetWidth(), paint->GetHeight());
}

void Render::draw() {
    epd.DisplayFrame();
}