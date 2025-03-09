
#include <iostream>
#include "bindings.hpp"
#include "stm32f7xx_hal.h"
#include <cstring>
#include <limits>

int main() {
    bindings::Init();

    int input;
    bool light = true;
    std::cout << "Hello World!\n" << std::endl;
    while (1) {
        //TODO: switch to interrupts to keep this backgrounded
        light = !light;
        bindings::red_led.Set(light);
        bindings::heartbeat.Set(light);
        
        std::cin >> input;
        // Check if the input is valid
        if (std::cin.fail()) {
            std::cin.clear(); // Clear the error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the invalid input
            std::cout << "Invalid input. Please enter a valid integer." << std::endl;
            continue; // Skip the rest of the loop and prompt for input again
        }
        
        if(input % 3 == 0) {
            std::cout << "Fizz";
        }
        if (input % 5 == 0) {
            std::cout << "Buzz";
        }
        if (input % 3 != 0 && input % 5 != 0) {
            std::cout << input;
        }
        std::cout << std::endl;
        

        bindings::DelayMs(100);

    }

    return 0;
}