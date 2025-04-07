
#include <stdio.h>
#include <cstring>
#include <iostream>
#include <string>
#include "bindings.hpp"

int main() {
    bindings::Init();

    std::string buf;
    bool pos = true;
    float voltage_outputs[10] = {};

    float current_measurement;
    uint8_t read_count = 0;
    while (1) {
        bindings::red_led.Set(pos);
        pos ^= 1;

       
        
        current_measurement += bindings::current_sensor.ReadCurrent()/255.0f;
        if(read_count++ == 255){
            std::cout << "average current measurement: " << std::to_string(current_measurement) << std::endl;
            current_measurement = 0.0f;
        }
        bindings::DelayMs(10);        

        // voltage_outputs[0] = bindings::analog_input_0.ReadVoltage();
        // voltage_outputs[1] = bindings::analog_input_1.ReadVoltage();
        // voltage_outputs[2] = bindings::analog_input_2.ReadVoltage();
        // voltage_outputs[3] = bindings::analog_input_3.ReadVoltage();
        // voltage_outputs[4] = bindings::analog_input_4.ReadVoltage();
        // voltage_outputs[5] = bindings::analog_input_5.ReadVoltage();
        // voltage_outputs[6] = bindings::analog_input_6.ReadVoltage();
        // voltage_outputs[7] = bindings::analog_input_7.ReadVoltage();
        // voltage_outputs[8] = bindings::analog_input_8.ReadVoltage();
        // voltage_outputs[9] = bindings::analog_input_9.ReadVoltage();

        // // for (int i = 0 ; i < bindings::kNumAnalogInputs; i++) {
        // //     std::cout << "Voltage on channel " << i << ": " << voltage_outputs[i] << std::endl;
        // // }

        // std::cout << "Current Meausrement: " << std::to_string(bindings::current_sensor.ReadCurrent()) << std::endl;
        // bindings::DelayMs(5000);

    }

    return 0;
}