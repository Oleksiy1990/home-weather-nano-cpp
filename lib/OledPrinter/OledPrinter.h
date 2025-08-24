#ifndef OLED_PRINTER_H
#define OLED_PRINTER_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

class OledPrinter {
    private: 
        static const uint8_t VERTICAL_GAP = 10;
        static const u_int8_t MAX_LINE = 5;
        static const u_int8_t MAX_CHARS_PER_LINE = 22; // Apparently display width is 21 chars, plus the last one for null
        char message_lines[MAX_LINE + 1][MAX_CHARS_PER_LINE] = {0};
        uint8_t width;
        uint8_t height;
        uint8_t i2c_address;
        TwoWire* i2c_port; 
        Serial_* serial_port = nullptr;
        int8_t reset_pin;
        uint8_t switchvcc;
        Adafruit_SSD1306 adafruit_display;

        bool save_message_line(char* msg, uint8_t line);
    public:
        OledPrinter(uint8_t width, uint8_t height, TwoWire* i2c_port, int8_t reset_pin, uint8_t switchvcc, uint8_t i2c_address);
        OledPrinter(uint8_t width, uint8_t height, uint8_t i2c_address);
        bool init();
        bool init(Serial_* serialport);
        bool write_line(char* message, uint8_t line = 0);
        void show_text();
};


#endif