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
    if (*serialport) {
        serial_port = serialport;
        uint16_t counter = 0;
        serial_port->println("Starting OLED SSD1306 on I2C...");
        while (!(this->init())){
            serial_port->print("Attempt to start OLED SSD1306 failed: ");
            serial_port->print(counter);
            serial_port->println(" times.");
            serial_port->flush();
            counter++;
            delay(1000);
        } 
        return true;
    }
    return this->init();
}

bool OledPrinter::write_line(char* message, uint8_t line){
    char error_msg[] = "Requested line low";
    if (!save_message_line(message, line)){
        save_message_line(error_msg, 0);
        if (serial_port != nullptr) {
            serial_port->println("Requested to print on a line that is more than the OLED 1306 display height.");
        }
        return false;
    }
    else{
        return true;
    }
}
void OledPrinter::show_text(){
    adafruit_display.clearDisplay();
    adafruit_display.setTextSize(1);
    adafruit_display.setTextColor(WHITE);
    for (uint8_t idx = 0; idx <= MAX_LINE; idx++){
        adafruit_display.setCursor(0, idx*VERTICAL_GAP);
        adafruit_display.println(message_lines[idx]);
    }
    adafruit_display.display();
}

bool OledPrinter::save_message_line(char* msg, uint8_t line){
    if (line > MAX_LINE) {
        return false;
    } 
    else {
        for (uint8_t idx = 0; idx < MAX_CHARS_PER_LINE; idx++){
            message_lines[line][idx] = *(msg + idx);
            if (*(msg + idx) == '\0'){
                break;
            }

        }
        return true;
    }
}