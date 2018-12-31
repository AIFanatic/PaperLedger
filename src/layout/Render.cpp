#include "Render.h"

Render::Render() {
    initDisplay();
};

Render::~Render() {
};

void Render::initDisplay() {
    io = new GxIO_Class(SPI, ELINK_SS, ELINK_DC, ELINK_RESET);
    display = new GxEPD_Class(*io, ELINK_RESET, ELINK_BUSY);

    SPI.begin(SPI_CLK, SPI_MISO, SPI_MOSI, -1);

    static bool isInit = false;
    if (isInit)
    {
        return;
    }
    isInit = true;
    display->init();
    display->setRotation(1);
    display->eraseDisplay();
    display->setTextColor(GxEPD_BLACK);
    display->setFont(&FreeMonoBold9pt7b);
    display->setTextSize(0);
}

void Render::clearScreen(bool partialUpdate) {
    display->eraseDisplay(partialUpdate);
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
            bool filled = obj["filled"];
            drawRectangle(x, y, w, h, color, filled);
        }
        else if(type.equals("circle")) {
            int r = obj["r"];
            bool filled = obj["filled"];
            drawCircle(x, y, r, color, filled);
        }
        else if(type.equals("text")) {
            const char *text = obj["text"];
            int size = obj["size"];
            int w = obj["w"];
            drawText(x, y, text, size, color, w);
        }
        else if(type.equals("image")) {
            int index = obj["index"];
            int mode = obj["mode"];
            int w = obj["w"];
            int h = obj["h"];
            drawImage(index, x, y, w, h, color, mode);
        }
        else if(type.equals("clear")) {
            bool partial = obj["partial"];
            clearScreen(partial);
        }
        else if(type.equals("fill")) {
            fillScreen(color);
        }
    }

    display->updateWindow(0, 0, GxEPD_WIDTH, GxEPD_HEIGHT, false);
}

void Render::fillScreen(int color) {
    display->fillScreen(color);
}

void Render::drawRectangle(int x, int y, int w, int h, int color, bool filled) {
    if(filled) {
        display->fillRect(x, y, w, h, color);
        return;
    }

    display->drawRect(x, y, w, h, color);
}

void Render::drawCircle(int x, int y, int r, int color, bool filled) {
    if(filled) {
        display->fillCircle(x, y, r, color);
        return;
    }

    display->drawCircle(x, y, r, color);
}

void Render::drawText(int x, int y, const char *text, int size, int color, int w) {
    setFont(size);
    display->setTextColor(color);
    display->setCursor(x, y);
    display->print(text);
}

void Render::setFont(int size) {
    if(currentFontSize != size) {
        const GFXfont *font = &FreeMonoBold24pt7b;

        if(size == 9) { font = &FreeMonoBold9pt7b; }
        else if(size == 12) { font = &FreeMonoBold12pt7b; }
        else if(size == 18) { font = &FreeMonoBold18pt7b; }
        else if(size == 24) { font = &FreeMonoBold24pt7b; }

        display->setFont(font);

        currentFontSize = size;
    }
}

void Render::drawImage(int index, int x, int y, int w, int h, int color, int mode) {
    display->drawBitmap(ICONS[index], x, y, w, h, color, mode);
}

void Render::draw() {
    display->updateWindow(0, 0, GxEPD_WIDTH, GxEPD_HEIGHT, false);
}

void Render::draw(int x, int y, int w, int h, bool adjustRotate) {
    display->updateWindow(x, y, w, h, adjustRotate);
}

void Render::getTextBounds(int x, int y, const char *text, uint16_t &w1, uint16_t &h1) {
    int16_t x1, y1;

    display->getTextBounds(text, x, y, &x1, &y1, &w1, &h1);
}