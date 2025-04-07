
#include <stdio.h>
#include <sys/_stdint.h>

#include <cstddef>
#include <cstring>
#include <iostream>
#include <string>
#include "bindings.hpp"


#include "network_cfg.hpp"

constexpr float nominalBaseCurrent = 0.05f; //Amps, base current for layers 
constexpr float nominalBaseVoltage = 5.5f; //Volts, base voltage for layers 

float bytesToFloat(uint8_t* bytes) {
    int32_t i = 0;
    i |= bytes[0] | (bytes[1] << 8) | (bytes[2] << 16) | (bytes[3] << 24);
    return (float) i / 10000.f;
}

float input_values[3][4] = {
    {0.1, 0.1, 0.1, 0.1},
    {0.1, 0.1, 0.1, 0.1},
    {0.1, 0.1, 0.1, 0.1}
};

float output_values[10];


int main() {
    bindings::Init();
    bindings::red_led.Set(1);
    bindings::green_led.Set(1);


    bool light = false;
    uint8_t input_buf[49] = {};
    uint8_t output_buf[40] = {};
    for(int i = 0; i < 40; i++){
        output_buf[i] = 0;
    }
    char mode_flag = 'V';
    model current_model = model::VISUAL;
    
    bindings::green_led.Set(1);
    program_model(current_model);
    bindings::green_led.Set(0);

    while (1) {



        bindings::red_led.Set(light);


        shared::uart::Message<shared::uart::MessageType::Receive> PCA_components{input_buf};
        bindings::uart_bus.ReceiveBlocking(PCA_components);

        if(PCA_components.Data()[0] != mode_flag){
            mode_flag = PCA_components.Data()[0];
            current_model = mode_flag == 'A' ? model::AUDIO : model::VISUAL;
            bindings::green_led.Set(1);
            program_model(current_model);
            bindings::green_led.Set(0);
        }
            
        for(int i = 0; i < 12; i++){
            input_values[i/4][i%4] = bytesToFloat(PCA_components.Data() + 1 + i*4);
        }

    
        bindings::analog_output_group_0.SetAndLoadAllVoltages(input_values[0]);
        bindings::analog_output_group_1.SetAndLoadAllVoltages(input_values[1]);
        bindings::analog_output_group_2.SetAndLoadAllVoltages(input_values[2]);



        for (int i = 0; i < 10; i++) {
            output_values[i] = 0.f;
            for(int j = 0; j < 16; j++){
                output_values[i] +=  bindings::adc_channels[i]->ReadVoltage() / 16.f;
            }
        }



        bindings::DelayMs(10);   

        bindings::SoftMax(output_values);

        int32_t value;
        for (int i = 0; i < 10; i++) {
            value = (int32_t) (output_values[i] * 10000.f);
            output_buf[i * 4] = (uint8_t) (value & 0xFF);
            output_buf[i * 4 + 1] = (uint8_t) (value >> 8) & 0xFF;
            output_buf[i * 4 + 2] = (uint8_t) (value >> 16) & 0xFF;
            output_buf[i * 4 + 3] = (uint8_t) (value >> 24) & 0xFF;
        }


        shared::uart::Message<shared::uart::MessageType::Transmit> SoftMax_Output{output_buf};
        bindings::uart_bus.Transmit(SoftMax_Output);
        
        light = !light;
        bindings::DelayMs(500);
    
        
    }

    return 0;
}