#ifndef I2C_SCANNER_H
#define I2C_SCANNER_H

#include <Arduino.h>
#include <Wire.h>

/**
 * This function scans the i2c port and prints out 
 * the addresses of connected devices over the default Serial 
 * for the board. Copied over form online forums.
 */

void scan_i2c_and_send_serial(arduino::TwoWire*);
bool float_to_string(char* output_val, float input_val, uint8_t precision, uint8_t max_length);

#endif