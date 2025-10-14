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
Adafruit_CCS811 gas_sensor;
// put function declarations here:

void setup() { 
  Serial.begin(9600);
  delay(2000); // this is just to make sure that Serial is up and running

  // oled.init(&Serial);
  Wire.begin();
  scan_i2c_and_send_serial(&Wire);

  while (!gas_sensor.begin(0x5a, &Wire)){
    Serial.println("Failed to start sensor! Please check your wiring.");
    delay(2000);
  }
  delay(2000);
  gas_sensor.setDriveMode(CCS811_DRIVE_MODE_1SEC);
  gas_sensor.setEnvironmentalData(55.5, 20.0);
  
}

void loop() {
  // scan_i2c_and_send_serial(&Wire);
  // sprintf(msg, "Hello world %d", counter);
  counter ++;
  // oled.write_line(msg, 1);
  // oled.show_text();
  delay(1500);
  while (!gas_sensor.available()){
    Serial.println("Data from CCS811 not available");
    // gas_sensor.SWReset();
    // gas_sensor.setDriveMode(CCS811_DRIVE_MODE_1SEC);
    // gas_sensor.disableInterrupt();
    // gas_sensor.setEnvironmentalData(55.5, 20.0);
    delay(2000);
  }
  if (gas_sensor.readData() == 0){
    sprintf(msg, "TVOC: %d", gas_sensor.getTVOC());
    Serial.println(msg);
    sprintf(msg, "eCO2: %d", gas_sensor.geteCO2());
    Serial.println(msg);
  }

}
