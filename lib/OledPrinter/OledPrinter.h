#ifndef OLED_READER_H
#define OLED_READER_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

class OledPrinter {
    private: 
        uint8_t width;
        uint8_t height;
        uint8_t i2c_address;
        TwoWire* i2c_port; 
        int8_t reset_pin;
        uint8_t switchvcc;
        Adafruit_SSD1306 adafruit_display;
    public:
        OledPrinter(uint8_t width, uint8_t height, TwoWire* i2c_port, int8_t reset_pin, uint8_t switchvcc, uint8_t i2c_address);
        OledPrinter(uint8_t width, uint8_t height, uint8_t i2c_address);
        bool init();
        bool init(Serial_* serialport);
        bool show_text(char* message);
};


#endif