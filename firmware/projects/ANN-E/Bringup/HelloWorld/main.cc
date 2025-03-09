
#include <iostream>
#include "bindings.hpp"
#include "stm32f7xx_hal.h"

int main() {
    bindings::Init();

    bool light = true;

    while (1) {
        //TODO: switch to interrupts to keep this backgrounded
        light = !light;
        bindings::red_led.Set(light);
        bindings::heartbeat.Set(light);
        bindings::DelayMs(1000);
        std::cout << "Hello World!\n" << std::endl;
    }

    return 0;
}