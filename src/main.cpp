#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include "Adafruit_CCS811.h"

Adafruit_CCS811 GasSensor;

// put function declarations here:

void setup() {
Serial.begin(19200);

  Serial.println("CCS811 test");

  while(!GasSensor.begin()){
    Serial.println("Failed to start sensor! Please check your wiring.");
    delay(1000);
  }

  // Wait for the sensor to be ready
  while(!GasSensor.available()){
    Serial.println("GasSensor not available");
    delay(1000);
  }
  GasSensor.setDriveMode(CCS811_DRIVE_MODE_1SEC);
}

void loop() {
  if(GasSensor.available()){
      if(!GasSensor.readData()){
        Serial.print("CO2: ");
        Serial.print(GasSensor.geteCO2());
        Serial.print("ppm, TVOC: ");
        Serial.println(GasSensor.getTVOC());
      }
      else{
        Serial.println("ERROR CCS811 readData() failed! Sleeping for 1000 ms");
        delay(1000);
      }
    }
    delay(500);

}
