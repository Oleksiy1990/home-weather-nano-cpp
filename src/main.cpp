#include <Arduino.h>
#include <Wire.h>
#include "helperfunctions.h"
#include "Adafruit_CCS811.h"
#include "OledPrinter.h"
#include "DHT20.h"
#include "Timer.h"
#include <cstdio>
#include <ArduinoLowPower.h>

#define OLED_I2C_ADDRESS 0x3C
#define CCS811_I2C_ADDRESS 0x5A


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define MAX_SIZE_FLOAT_TO_STRING 11
#define PRECISION_FLOAT_TO_STRING 3


OledPrinter oled{SCREEN_WIDTH, SCREEN_HEIGHT, OLED_I2C_ADDRESS};

DHT20 temperature_humidity_sensor(&Wire);
float current_temperature;
float current_humidity;

Timer timer_ms(MILLIS);
int counter = 0;
char msg[50];
Adafruit_CCS811 gas_sensor;
char float_string_representation[MAX_SIZE_FLOAT_TO_STRING];

enum class State {initialization, temperature_humidity_sensing, gas_sensing, dust_sensing};
State current_state;

void setup() { 
  current_state = State::initialization;
  Wire.begin();
  Serial.begin(9600);
  delay(2000); // this is just to make sure that Serial is up and running
  Serial.println("Serial communication initialized!");

  // The first time we list all I2C devices (maybe to be removed later)
  scan_i2c_and_send_serial(&Wire);

  // Initialize OLED
  if (oled.init(&Serial)){
    Serial.println("OLED initialized");
  }
  else {
    while (!oled.init(&Serial)) {
      Serial.println("OLED NOT initialized");
      delay(2000); // this is just to make sure that Serial is up and running
    }
    Serial.println("OLED initialized");
  }
  sprintf(msg, "OLED init OK");
  oled.write_line(msg, 1);
  oled.show_text();
  delay(2000); // this is just to make sure that Serial is up and running

  // First deal with setting up the temperature/humidity sensor
  if (temperature_humidity_sensor.begin()){
    Serial.println("DHT20 temperature/humidity sensor initialized");
  } 
  else {
    while (!temperature_humidity_sensor.begin()) {
      Serial.println("DHT20 temperature/humidity sensor NOT initialized, trying again...");
      sprintf(msg, "DHT20 init FAIL");
      oled.write_line(msg, 1);
      oled.show_text();
      delay(2000);
    }
    Serial.println("DHT20 temperature/humidity sensor initialized");
  }
  sprintf(msg, "DHT20 init OK");
  oled.write_line(msg, 1);
  oled.show_text();
  delay(2000);

  if (temperature_humidity_sensor.isConnected()){
    Serial.println("DHT20 temperature/humidity sensor connected");
  } 
  else {
    while (!temperature_humidity_sensor.isConnected()) {
      Serial.println("DHT20 temperature/humidity sensor NOT connected, trying again...");
      sprintf(msg, "DHT20 conn FAIL");
      oled.write_line(msg, 1);
      oled.show_text();
      delay(2000);
    }
    Serial.println("DHT20 temperature/humidity sensor connected");
  }
  sprintf(msg, "DHT20 conn OK");
  oled.write_line(msg, 1);
  oled.show_text();
  delay(2000);


  // Start CCS811 gas sensor here
  if (gas_sensor.begin(CCS811_ADDRESS, &Wire)) {
    Serial.println("CCS811 gas sensor started");
  }
  else {
    while (!gas_sensor.begin(CCS811_ADDRESS, &Wire)){
      Serial.println("CCS811 gas sensor NOT started. Trying again...");
      sprintf(msg, "CCS811 init FAIL");
      oled.write_line(msg, 1);
      oled.show_text();
      delay(2000);
    }
    Serial.println("CCS811 gas sensor started");
  }
  sprintf(msg, "CCS811 init OK");
  oled.write_line(msg, 1);
  oled.show_text();
  delay(2000);

  gas_sensor.setDriveMode(CCS811_DRIVE_MODE_1SEC);
  gas_sensor.setEnvironmentalData(55.5, 20.0);
  
  timer_ms.start();
  Serial.println("Timer started!");
  delay(2000);
}

void loop() {
  // This is for testing purposes, to be deleted
  sprintf(msg, "Hello world %d", counter);
  counter ++;
  oled.write_line(msg, 1);

  switch(current_state){
    case State::initialization:
      oled.clear_display();
      if (timer_ms.read() > 1500){
        current_state = State::temperature_humidity_sensing;
      }
      else {
        delay(150);
        // LowPower.sleep(150);
      }
      break;
    case State::temperature_humidity_sensing:
      if (!temperature_humidity_sensor.isConnected()){ // there has to be a function like "reconnect"
        temperature_humidity_sensor.begin();
        Serial.println("DHT20 sensor reconnected");
      }
      temperature_humidity_sensor.read();
      current_temperature = temperature_humidity_sensor.getTemperature();
      current_humidity = temperature_humidity_sensor.getHumidity();

      //Convert temperature float to string and print
      float_to_string(float_string_representation, current_temperature, PRECISION_FLOAT_TO_STRING, MAX_SIZE_FLOAT_TO_STRING);
      sprintf(msg, "Temperature: %s", float_string_representation);
      Serial.println(msg);
      oled.write_line(msg, 1);
      //Convert humidity float to string and print
      float_to_string(float_string_representation, current_humidity, PRECISION_FLOAT_TO_STRING, MAX_SIZE_FLOAT_TO_STRING);
      sprintf(msg, "Humidity: %s", float_string_representation);
      Serial.println(msg);
      oled.write_line(msg, 2);
      oled.show_text();

      timer_ms.stop();
      timer_ms.start();

      gas_sensor.setEnvironmentalData(current_humidity, current_temperature); // set data to gas sensor before sleeping

      delay(2000);
      // LowPower.sleep(2000);
      current_state = State::gas_sensing;
      break;
    case State::gas_sensing:
      while (!gas_sensor.available()){
        Serial.println("Data from CCS811 not available");
        // gas_sensor.SWReset();
        // gas_sensor.setDriveMode(CCS811_DRIVE_MODE_1SEC);
        // gas_sensor.disableInterrupt();
        // gas_sensor.setEnvironmentalData(55.5, 20.0);
        // LowPower.sleep(2000);
        delay(2000);
      }
      gas_sensor.readData();
      sprintf(msg, "TVOC: %d ppb", gas_sensor.getTVOC());
      Serial.println(msg);
      oled.write_line(msg, 1);
      if (gas_sensor.getTVOC() <= 65){
        sprintf(msg, "TVOC ist super");
      }
      else if (gas_sensor.getTVOC() > 65 && gas_sensor.getTVOC() <= 220) {
        sprintf(msg, "Vielleicht luften");
      }
      else if (gas_sensor.getTVOC() > 220 && gas_sensor.getTVOC() <= 660) {
        sprintf(msg, "Bitte luften");
      }
      else {
        sprintf(msg, "Dringend luften");
      }
      oled.write_line(msg, 2);

      sprintf(msg, "eCO2: %d ppm", gas_sensor.geteCO2());
      Serial.println(msg);
      oled.write_line(msg, 3);
      if (gas_sensor.geteCO2() <= 600){
        sprintf(msg, "CO2 ist gut");
      }
      else if (gas_sensor.geteCO2() > 600 && gas_sensor.geteCO2() <= 1000) {
        sprintf(msg, "Luften notwendig");
      }
      else {
        sprintf(msg, "Dringend luften");
      }
      oled.write_line(msg, 4);
      oled.show_text();

      // LowPower.sleep(2000);
      delay(2000);
      current_state = State::initialization;
      break;
    default:
      Serial.println("Entered the default case, which we should not enter");
      break;
  }

}
