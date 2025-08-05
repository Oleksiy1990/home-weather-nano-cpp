#include <Arduino.h>
#include <Wire.h>
#include "i2c_scanner.h"
#include "Adafruit_CCS811.h"
#include "OledPrinter.h"


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

OledPrinter oled{SCREEN_WIDTH, SCREEN_HEIGHT, 0x3c};
int counter = 0;
char msg[50];

// put function declarations here:

void setup() { 
  Serial.begin(9600); // it seems like one cannot print from setup()
  oled.init(&Serial);
}

void loop() {
  scan_i2c_and_send_serial(&Wire);
  sprintf(msg, "Hello world %d", counter);
  counter ++;
  oled.show_text(msg);
  delay(500);

}
