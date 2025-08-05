#include <Arduino.h>
#include <Wire.h>
#include "i2c_scanner.h"
#include "Adafruit_CCS811.h"


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


// put function declarations here:

void setup() {
  Serial.begin(9600);
  while (!Serial){
    ;
  }
  Wire.begin();

  while(!display.begin(SSD1306_SWITCHCAPVCC, 0x3c)) { // apparently 0x3c is the i2c address of this OLED
    Serial.println(F("SSD1306 OLED allocation failed"));
    delay(1000);
  }

}

void loop() {
  scan_i2c_and_send_serial(&Wire);
  delay(1000);      

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println("Hello world");
  display.display();
  delay(500);
}
