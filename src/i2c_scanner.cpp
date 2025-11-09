#include "i2c_scanner.h"

void scan_i2c_and_send_serial(TwoWire* wire){
  wire->begin(); 
  uint8_t error, address;
  int nDevices;
  Serial.println("Scanning the I2C bus...");
  nDevices = 0;
  for(address = 1; address < 127; address++ ) {
    wire -> beginTransmission(address);
    error = wire -> endTransmission();
    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address<16) {
        Serial.print("0");
      }
      Serial.println(address,HEX);
      nDevices++;
    }
    else {
      if (error==4){
        Serial.print("Unknow error at address 0x");
        if (address<16) {
          Serial.print("0");
        }
        Serial.println(address,HEX);
      }
    }    
  }
  if (nDevices == 0) {
    Serial.println("No I2C devices found\n");
  }
  else {
    Serial.println("done\n");
  }
}