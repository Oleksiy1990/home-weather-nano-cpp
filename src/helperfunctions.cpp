#include "helperfunctions.h"
#include "math.h"

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

bool float_to_string(char* output_val, float input_val, uint8_t precision, uint8_t max_length){
  int format_result;
  int intpart = (int)input_val;
  int decpart = (int)(pow(10., (float)precision)*abs((input_val - intpart)));
  format_result = snprintf(output_val, max_length ,"%d", intpart);
  if ((format_result > 0) && (max_length - format_result > 1)){
    format_result = snprintf(output_val + format_result, max_length - format_result,".%d", decpart);
  }
  return (format_result > 0);
}