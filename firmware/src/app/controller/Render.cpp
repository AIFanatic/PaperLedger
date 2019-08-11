#include "Render.h"

Render::Render() {
    initDisplay();
};

Render::~Render() {
};

void Render::initDisplay() {
    display = new GxEPD2_BW<GxEPD2_290, GxEPD2_290::HEIGHT> (GxEPD2_290(ELINK_SS, ELINK_DC, ELINK_RESET, ELINK_BUSY));

    SPI.begin(SPI_CLK, SPI_MISO, SPI_MOSI, -1);

    display->init(115200, false);
    display->setRotation(3);
    display->mirror(false);
    display->setTextColor(GxEPD_BLACK);
    display->setFont(&FreeSans9pt7b);
    display->setTextSize(0);
}

void Render::clearScreen() {
    // display->clearScreen();
    drawRectangle(0, 0, display->width(), display->height(), BLACK, true);
    draw();
    drawRectangle(0, 0, display->width(), display->height(), WHITE, true);
    draw();
    drawRectangle(0, 0, display->width(), display->height(), BLACK, true);
    draw();
    drawRectangle(0, 0, display->width(), display->height(), WHITE, true);
    draw();
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
        else if(type.equals("triangle")) {
            int x0 = obj["x0"];
            int y0 = obj["y0"];
            int x1 = obj["x1"];
            int y1 = obj["y1"];
            int x2 = obj["x2"];
            int y2 = obj["y2"];
            bool filled = obj["filled"];
            drawTriangle(x0, y0, x1, y1, x2, y2, color, filled);
        }
        else if(type.equals("arc")) {
            int x = obj["x"];
            int y = obj["y"];
            int startAngle = obj["startAngle"];
            int endAngle = obj["endAngle"];
            int radius = obj["r"];
            int color = obj["color"];
            drawArc(x, y, startAngle, endAngle, radius, color);
        }
        else if(type.equals("text")) {
            const char *text = obj["text"];
            int size = obj["size"];
            int align = obj["align"];
            drawText(x, y, text, size, color, align);
        }
        else if(type.equals("image")) {
            int index = obj["index"];
            int w = obj["w"];
            int h = obj["h"];
            drawImage(index, x, y, w, h, color);
        }
        else if(type.equals("clear")) {
            clearScreen();
        }
        else if(type.equals("fill")) {
            fillScreen(color);
        }
    }

    draw();
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

void Render::drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, int color, bool filled) {
    if(filled) {
        display->fillTriangle(x0, y0, x1, y1, x2, y2, color);
        return;
    }

    display->drawTriangle(x0, y0, x1, y1, x2, y2, color);
}

void Render::drawArc(int x, int y, int startAngle, int endAngle, int radius, int color) {
    for (int i = startAngle; i < endAngle; i++) {
        int pX = x + cos((i-90)*3.14/180) * radius;
        int pY = y + sin((i-90)*3.14/180) * radius;
        drawPixel(pX, pY, BLACK);
    }
}

void Render::drawText(int x, int y, const char *text, int size, int color, int alignment) {
    int16_t x1, y1;
    uint16_t w, h;

    setFont(size);
    display->setTextColor(color);
    display->getTextBounds(text, x, y, &x1, &y1, &w, &h);

    switch (alignment)
    {
        case NO_ALIGNMENT:
            display->setCursor(x, y);
            break;
        case LEFT_ALIGNMENT:
            display->setCursor(0, y);
            break;
        case RIGHT_ALIGNMENT:
            display->setCursor(display->width() - w - x1, y);
            break;
        case CENTER_ALIGNMENT:
            display->setCursor(display->width() / 2 - ((w + x1) / 2), y);
            break;
        default:
            break;
    }

    display->print(text);
}

void Render::drawPixel(int x, int y, int color) {
    display->drawPixel(x, y, color);
}

void Render::setFont(int size) {
    if(currentFontSize != size) {
        const GFXfont *font = &FreeSans24pt7b;

        if(size == 9) { font = &FreeSans9pt7b; }
        else if(size == 12) { font = &FreeSans12pt7b; }
        else if(size == 18) { font = &FreeSans18pt7b; }
        else if(size == 24) { font = &FreeSans24pt7b; }
        
        else if(size == 7) { font = &FreeSans7pt7b; }
        else if(size == 8) { font = &FreeSans8pt7b; }

        display->setFont(font);

        currentFontSize = size;
    }
}

void Render::drawImage(int index, int x, int y, int w, int h, int color) {
    display->drawBitmap(x, y, ICONS[index], w, h, color);
}

void Render::drawImage(const unsigned char *bitmap, int x, int y, int w, int h, int color) {
    display->drawBitmap(x, y, bitmap, w, h, color);
}

void Render::draw() {
    display->displayWindow(0, 0, GxEPD2_290::HEIGHT, GxEPD2_290::WIDTH);
}

void Render::draw(int x, int y, int w, int h, bool adjustRotate) {
    display->displayWindow(x, y, h, w);
}

void Render::getTextBounds(int x, int y, const char *text, uint16_t &w1, uint16_t &h1) {
    int16_t x1, y1;

    display->getTextBounds(text, x, y, &x1, &y1, &w1, &h1);
}