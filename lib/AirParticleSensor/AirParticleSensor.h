#ifndef AIR_PARTICLE_SENSOR_H
#define AIR_PARTICLE_SENSOR_H

#include <stdint.h>
#include <Arduino.h>

class AirParticleSensor {
    private: 

        Uart* serial_communicator{nullptr};

        static const char startchar1 = 0x42;
        static const char startchar2 = 0x4d;
        static const uint8_t message_length_bytes = 32;
        static const uint8_t bytes_per_meas = 2;

        // There are PM values, given in microgram per cubic meter 
        static const uint8_t start_pm_1p0_atm = 10;
        static const uint8_t start_pm_2p5_atm = 12;
        static const uint8_t start_pm_10_atm = 14;

        // the next ones, according to the manual, are number of particles greater than that size in 0.1 L of air
        static const uint8_t start_0p3_micron = 16;
        static const uint8_t start_0p5_micron = 18;
        static const uint8_t start_1p0_micron = 20;
        static const uint8_t start_2p5_micron = 22;
        static const uint8_t start_5_micron = 24;
        static const uint8_t start_10_micron = 26;

        char full_message[message_length_bytes];
        
        bool read_full_message();
    public:
        AirParticleSensor();
        void init(Uart* serialport);
        uint16_t get_pm_1p0(); 
        uint16_t get_pm_2p5(); 
        uint16_t get_pm_10(); 
        uint16_t get_above_0p3_micron();
        uint16_t get_above_0p5_micron();
        uint16_t get_above_1p0_micron();
        uint16_t get_above_2p5_micron();
        uint16_t get_above_5_micron();
        uint16_t get_above_10_micron();
};


#endif