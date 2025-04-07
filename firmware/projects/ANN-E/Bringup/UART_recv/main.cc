
#include <sys/_stdint.h>
#include <iostream>
#include "bindings.hpp"
#include "stm32f7xx_hal.h"
#include <cstring>
#include <limits>
#include <string>

float bytesToFloat(uint8_t* bytes) {
    int32_t i = 0;
    i |= bytes[0] | (bytes[1] << 8) | (bytes[2] << 16) | (bytes[3] << 24);
    return (float) i / 10000.f;
}
std::string mystr;
int main() {
    bindings::Init();

    // std::cout << "Hello World!" << std::endl;
    bindings::red_led.Set(1);
    uint8_t buf[53] = {0};
    uint8_t check[] = "ANN-E";
    shared::uart::Message<shared::uart::MessageType::Receive> msg{buf};

    bindings::uart_bus.ReceiveBlocking(msg);
    // std::cout << msg.Data() << std::endl;
    bindings::green_led.Set(1);

    bool led = true;   
    std::cout<< "reception" << std::endl;     
    

    for(int i = 0; i < 5; i++){
        std::cout<< msg.Data()[i] << std::endl;
    }

    float f;
    for (int i = 5; i < 53; i+=4){
        f = bytesToFloat(msg.Data()+i);
        std::cout<<std::to_string(f)<< std::endl;
    }



    



    bindings::red_led.Set(led);

    while (1) {

    }

    return 0;
}