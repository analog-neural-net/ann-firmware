
#include <stdio.h>
#include <sys/_stdint.h>

#include <cstddef>
#include <cstring>
#include <iostream>
#include <string>
#include "bindings.hpp"


#include "network_cfg.hpp"
#include "projects/ANN-E/Bringup/LayerBoard/bindings.hpp"

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



    for (int i = 0; i < bindings::kNumNeuronsPerLayer; i++) {
        for (int j = 0; j < bindings::kNumWeightsPerNeuron; j++) {
            bindings::pots[0][i][j].SetPosition(neurons_pot_positions[i][j]);
            bindings::DelayMs(10);
            bindings::pots[0][i][j].SetTerminalConnections(
                neuron_tcona_settings[i][j],
                neuron_tconb_settings[i][j],
                neuron_tconw_settings[i][j]
            );
        }
        bindings::bias_pots[0][i].SetPosition(bias_pot_positions[i]);
        bindings::bias_pots[0][i].SetTerminalConnections(
            bias_tcona_settings[i],
            bias_tconb_settings[i],
            bias_tconw_settings[i]
        );
        bindings::fb_pots[0][i].SetPosition(feedback_pot_positions[i]);
        bindings::fb_pots[0][i].SetTerminalConnections(
            feedback_tcona_settings[i],
            feedback_tconb_settings[i],
            feedback_tconw_settings[i]
        );
    }

    for (int i = 0; i < bindings::kNumNeuronsPerLayerOutput; i++) {
        for (int j = 0; j < bindings::kNumWeightsPerNeuron; j++) {
            bindings::pots[1][i][j].SetPosition(neurons_pot_positions_2[i][j]);
            bindings::DelayMs(10);
            bindings::pots[1][i][j].SetTerminalConnections(
                neuron_tcona_settings_2[i][j],
                neuron_tconb_settings_2[i][j],
                neuron_tconw_settings_2[i][j]
            );
        }
        bindings::bias_pots[1][i].SetPosition(bias_pot_positions_2[i]);
        bindings::bias_pots[1][i].SetTerminalConnections(
            bias_tcona_settings_2[i],
            bias_tconb_settings_2[i],
            bias_tconw_settings_2[i]
        );
        bindings::fb_pots[1][i].SetPosition(feedback_pot_positions_2[i]);
        bindings::fb_pots[1][i].SetTerminalConnections(
            feedback_tcona_settings_2[i],
            feedback_tconb_settings_2[i],
            feedback_tconw_settings_2[i]
        );
    }

    bool light = false;
    uint8_t input_buf[53] = {};
    uint8_t output_buf[40] = {};

    while (1) {

        bindings::red_led.Set(light);

        // uint8_t check[] = "ANN-E";
        shared::uart::Message<shared::uart::MessageType::Receive> PCA_components{input_buf};
        bindings::uart_bus.ReceiveBlocking(PCA_components);
        for(int i = 0; i < 12; i++){
            input_values[i/4][i%4] = bytesToFloat(PCA_components.Data() + 5 + i*4);
        }
    
        for(int i = 0; i < 12; i++){
            std::cout << std::to_string(input_values[i/4][i%4]) << std::endl;
        }
    
        bindings::green_led.Set(1);
    
        bindings::analog_output_group_0.SetAndLoadAllVoltages(input_values[0]);
        bindings::analog_output_group_1.SetAndLoadAllVoltages(input_values[1]);
        bindings::analog_output_group_2.SetAndLoadAllVoltages(input_values[2]);

        for (int i = 0; i < 10; i++) {
            output_values[i] = 0.f;
            for(int j = 0; j < 16; j++){
                output_values[i] +=  bindings::adc_channels[i]->ReadVoltage() / 16.f;
            }
        }

        bindings::SoftMax(output_values);

        for (int i = 0; i < 10; i++) {
            output_buf[i * 4] = (uint8_t) (output_values[i] * 10000.f);
            output_buf[i * 4 + 1] = (uint8_t) ((output_values[i] * 10000.f)) >> 8;
            output_buf[i * 4 + 2] = (uint8_t) ((output_values[i] * 10000.f)) >> 16;
            output_buf[i * 4 + 3] = (uint8_t) ((output_values[i] * 10000.f)) >> 24;
        }
        shared::uart::Message<shared::uart::MessageType::Transmit> SoftMax_Output{output_buf};

        
        light = !light;
        bindings::DelayMs(500);
        
        
    }

    return 0;
}