#include "Render.h"

Render::Render() {
    initDisplay();
    clearScreen();
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

        if(type.equals("rectangle")) {
            int w = obj["w"];
            int h = obj["h"];
            drawRectangle(x, y, w, h, color);
            addImageToFrameCentered(x, y);
        }
        else if(type.equals("circle")) {
            int r = obj["r"];
            drawCircle(x, y, r, color);
            addImageToFrameCentered(x, y);
        }
        else if(type.equals("text")) {
            const char *text = obj["text"];
            drawText(x, y, text, color);
            addImageToFrameCentered(x, y, true);
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
    }

    epd.DisplayFrame();
}

void Render::drawRectangle(int x, int y, int w, int h, int color) {
    paint->SetWidth(h+8);
    paint->SetHeight(w+8);

    paint->Clear(!color);
    paint->DrawRectangle(4, 4, w+4, h+4, color);
}

void Render::drawCircle(int x, int y, int r, int color) {
    paint->SetWidth(r*2+8);
    paint->SetHeight(r*2+8);

    paint->Clear(!color);
    paint->DrawCircle(r+4, r+4, r, color);
}

void Render::drawText(int x, int y, const char *text, int color) {
    // 18 px per letter - font24
    int w = strlen(text) * 18;
    paint->SetWidth(24); // Should be 32
    paint->SetHeight(w);

    paint->Clear(!color);
    paint->DrawStringAt(0, 2, text, &Font24, color);
}

void Render::drawImage(int index, int x, int y, int w, int h) {
    if(index < 0 || index >= (sizeof(ICONS)/sizeof(const unsigned char* const))) {
        Serial.println("Invalid image index");
        return;
    }
    epd.SetFrameMemory(ICONS[index], y, x, w, h);
    epd.SetFrameMemory(ICONS[index], y, x, w, h);
}

void Render::addImageToFrameCentered(int x, int y, bool startsFromTop) {
    // Flip coordinates
    int img_center_x = y - (paint->GetHeight() / 2);
    int img_center_y = x - (paint->GetWidth() / 2);
    
    if(startsFromTop) {
        img_center_x = y - (paint->GetWidth() / 2);
        img_center_y = x - (paint->GetHeight() / 2);
    }

    epd.SetFrameMemory(paint->GetImage(), img_center_x, img_center_y, paint->GetWidth(), paint->GetHeight());
}

void Render::addImageToFrame(int x, int y) {
    epd.SetFrameMemory(paint->GetImage(), x, y, paint->GetWidth(), paint->GetHeight());
}


// [
// 	{
// 		"type": "circle",
//         "x": 10,
//         "y": 10,
//         "r": 10,
//         "color": 1
// 	},
// 	{
// 		"type": "rectangle",
//         "x": 10,
//         "y": 10,
//         "w": 10,
//         "h": 10,
//         "color": 1
// 	}
// ]