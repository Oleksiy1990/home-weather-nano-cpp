#include "AirParticleSensor.h"

AirParticleSensor::AirParticleSensor(){}

void AirParticleSensor::init(Uart* serialport){
    serial_communicator = serialport;
}

bool AirParticleSensor::read_full_message(){
    memset(full_message, 0, message_length_bytes);
    char read_now{0};
    size_t bytes_after_preamble{0};

    // First we detect the preamble
    while (this->serial_communicator->available() > 0){
        read_now = this->serial_communicator->read();
        if (read_now == startchar1) {
            full_message[0] = startchar1;
        }
        if ((read_now == startchar2) && (full_message[0] == startchar1)){
            full_message[1] = startchar2;
            break; // here we have detected the preamble
        }
    }
    // Now we try to read the rest of the message
    if ((full_message[0] == startchar1) && (full_message[1] == startchar2)){
        bytes_after_preamble = serial_communicator->readBytes(full_message + 2, message_length_bytes - 2);
    }
    // return true if read the correct number of bytes, otherwise false
    return (bytes_after_preamble == (message_length_bytes - 2));
}

uint16_t AirParticleSensor::get_pm_1p0(){
    return (full_message[start_pm_1p0_atm] << 8) | full_message[start_pm_1p0_atm + 1];
}
uint16_t AirParticleSensor::get_pm_2p5(){
    return (full_message[start_pm_2p5_atm] << 8) | full_message[start_pm_2p5_atm + 1];
}
uint16_t AirParticleSensor::get_pm_10(){
    return (full_message[start_pm_10_atm] << 8) | full_message[start_pm_10_atm + 1];
}
uint16_t AirParticleSensor::get_above_0p3_micron(){
    return (full_message[start_0p3_micron] << 8) | full_message[start_0p3_micron + 1];
}
uint16_t AirParticleSensor::get_above_0p5_micron(){
    return (full_message[start_0p5_micron] << 8) | full_message[start_0p5_micron + 1];
}
uint16_t AirParticleSensor::get_above_1p0_micron(){
    return (full_message[start_1p0_micron] << 8) | full_message[start_1p0_micron + 1];
}
uint16_t AirParticleSensor::get_above_2p5_micron(){
    return (full_message[start_2p5_micron] << 8) | full_message[start_2p5_micron + 1];
}
uint16_t AirParticleSensor::get_above_5_micron(){
    return (full_message[start_5_micron] << 8) | full_message[start_5_micron + 1];
}
uint16_t AirParticleSensor::get_above_10_micron(){
    return (full_message[start_10_micron] << 8) | full_message[start_10_micron + 1];
}