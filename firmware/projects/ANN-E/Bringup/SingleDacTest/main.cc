
#include <stdio.h>

#include <cstring>
#include <iostream>

#include "bindings.hpp"
#include "projects/Demo/DigitalAnalogConverter/bindings.hpp"

int main() {
    bindings::Init();

    std::string buf;
    bool pos = true;
    float voltage_outputs[4] = {0, 0, 0, 0};

    while (1) {
        bindings::red_led.Set(pos);
        pos ^= 1;

        bindings::DelayMs(500);

        std::cout << "Enter a value for channel 0:" << std::endl;
        std::cin >> buf;
        voltage_outputs[0] = std::stof(buf);

        std::cout << "Enter a value for channel 1:" << std::endl;
        std::cin >> buf;
        voltage_outputs[1] = std::stof(buf);

        std::cout << "Enter a value for channel 2:" << std::endl;
        std::cin >> buf;
        voltage_outputs[2] = std::stof(buf);

        std::cout << "Enter a value for channel 3:" << std::endl;
        std::cin >> buf;
        voltage_outputs[3] = std::stof(buf);

        bindings::analog_output_group.SetAndLoadAllVoltages(voltage_outputs);
    }

    return 0;
}