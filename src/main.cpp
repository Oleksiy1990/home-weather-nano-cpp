#include <Arduino.h>
#include <Wire.h>
#include "i2c_scanner.h"
#include "Adafruit_CCS811.h"
#include "OledPrinter.h"
#include "AirParticleSensor.h"


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

OledPrinter oled{SCREEN_WIDTH, SCREEN_HEIGHT, 0x3c};
AirParticleSensor particle_sensor;
int counter = 0;
char msg[50];

// put function declarations here:

void setup() { 
  Serial.begin(9600);
  delay(2000); // this is just to make sure that Serial is up and running
  oled.init(&Serial);
  Serial1.begin(9600);
  delay(2000); // this is just to make sure that Serial is up and running
  particle_sensor.init(&Serial1);
}

void loop() {
  // scan_i2c_and_send_serial(&Wire);
  sprintf(msg, "Hello world %d", counter);
  counter ++;
  oled.write_line(msg, 0);
  oled.show_text();
  delay(500);

  // Serial.println("Serial1 data...");
  // while (Serial1.available()){
  //   char data = Serial1.read();
  //   Serial.print(data, HEX);
  // }
  Serial.println("PM 1.0: ");
  Serial.println(particle_sensor.get_pm_1p0());
  delay(1000);
  Serial.println("PM 2.5: ");
  Serial.println(particle_sensor.get_pm_2p5());
  delay(1000);
  Serial.println("PM 10: ");
  Serial.println(particle_sensor.get_pm_10());
  delay(1000);
  Serial.println("Above 0.3 microns: ");
  Serial.println(particle_sensor.get_above_0p3_micron());
  delay(1000);
  Serial.println("Above 0.5 microns: ");
  Serial.println(particle_sensor.get_above_0p5_micron());
  delay(1000);
  Serial.println("Above 1.0 microns: ");
  Serial.println(particle_sensor.get_above_1p0_micron());
  delay(1000);
  Serial.println("Above 2.5 microns: ");
  Serial.println(particle_sensor.get_above_2p5_micron());
  delay(1000);
  Serial.println("Above 5 microns: ");
  Serial.println(particle_sensor.get_above_5_micron());
  delay(1000);
  Serial.println("Above 10 microns: ");
  Serial.println(particle_sensor.get_above_10_micron());
  delay(1000);
  Serial.println("");
  delay(1000);

}
