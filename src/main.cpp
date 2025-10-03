#include <Arduino.h>
#include <Wire.h>
#include "helperfunctions.h"
#include "Adafruit_CCS811.h"
#include "OledPrinter.h"
#include "DHT20.h"
#include "Timer.h"
#include <cstdio>


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define MAX_SIZE_FLOAT_TO_STRING 11
#define PRECISION_FLOAT_TO_STRING 3

OledPrinter oled{SCREEN_WIDTH, SCREEN_HEIGHT, 0x3c};
DHT20 temperature_humidity(&Wire);
float current_temperature;
float current_humidity;

Timer timer_ms(MILLIS);
int counter = 0;
char msg[50];
char float_string_representation[MAX_SIZE_FLOAT_TO_STRING];

// put function declarations here:

void setup() { 
  bool is_ok;
  Wire.begin();
  Serial.begin(9600);
  delay(2000); // this is just to make sure that Serial is up and running
  Serial.println("Serial communication initialized!");
  is_ok = temperature_humidity.begin();
  Serial.println("DHT20 sensor initialized with result...");
  Serial.println(is_ok);
  is_ok = temperature_humidity.isConnected();
  Serial.println("Is DHT20 Sensor connected...");
  Serial.println(is_ok);
  is_ok = oled.init(&Serial);
  Serial.println("OLED initialized with result...");
  Serial.println(is_ok);
  timer_ms.start();
  Serial.println("Timer started!");
}

void loop() {
  // scan_i2c_and_send_serial(&Wire);
  if (!temperature_humidity.isConnected()){
    temperature_humidity.begin();
    Serial.println("DHT20 sensor reconnected");
  }
  sprintf(msg, "Hello world %d", counter);
  counter ++;
  oled.write_line(msg, 0);
  // int8_t temp_hum_read_result = temperature_humidity.read();

  if (timer_ms.read() > 1500){
    temperature_humidity.read();
    current_temperature = temperature_humidity.getTemperature();
    current_humidity = temperature_humidity.getHumidity();

    //Convert temperature float to string and print
    float_to_string(float_string_representation, current_temperature, PRECISION_FLOAT_TO_STRING, MAX_SIZE_FLOAT_TO_STRING);
    sprintf(msg, "Temperature: %s", float_string_representation);
    oled.write_line(msg, 1);

    //Convert humidity float to string and print
    float_to_string(float_string_representation, current_humidity, PRECISION_FLOAT_TO_STRING, MAX_SIZE_FLOAT_TO_STRING);
    sprintf(msg, "Humidity: %s", float_string_representation);
    oled.write_line(msg, 2);

    timer_ms.stop();
    timer_ms.start();
  }
  oled.show_text();
  delay(500);

}
