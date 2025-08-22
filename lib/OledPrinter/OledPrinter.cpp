#include "OledPrinter.h"

OledPrinter::OledPrinter(uint8_t width, uint8_t height, TwoWire* i2c_port, int8_t reset_pin, uint8_t switchvcc, uint8_t i2c_address)    
    : width{width}, height {height}, i2c_port{i2c_port}, reset_pin{reset_pin}, switchvcc{switchvcc}, i2c_address{i2c_address}, 
        adafruit_display{this->width, this->height, this->i2c_port, this->i2c_address}{};
OledPrinter::OledPrinter(uint8_t width, uint8_t height, uint8_t i2c_address)
    : width{width}, height{height}, i2c_address{i2c_address},
        i2c_port{&Wire}, reset_pin{-1}, switchvcc{SSD1306_SWITCHCAPVCC},
            adafruit_display{this->width, this->height, this->i2c_port, this->i2c_address}{};
bool OledPrinter::init(){
    if (!(i2c_port->available())){
        i2c_port->begin();
    }
    return adafruit_display.begin(switchvcc, i2c_address);
}
bool OledPrinter::init(Serial_* serialport){
    if (serialport->available()) {
        uint16_t counter = 0;
        while (!(this->init())){
            serialport->print("Attempt to start OLED SSD1306 failed: ");
            serialport->print(counter);
            serialport->println(" times.");
            serialport->flush();
            counter++;
            delay(1000);
        } 
        return true;
    }
    return this->init();
}
bool OledPrinter::show_text(char* message){
  adafruit_display.clearDisplay();
  adafruit_display.setTextSize(1);
  adafruit_display.setTextColor(WHITE);
  adafruit_display.setCursor(0, 10);
  adafruit_display.println(message);
  adafruit_display.display();
}