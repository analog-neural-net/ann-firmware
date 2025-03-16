
#include <stdio.h>
#include <sys/_stdint.h>

#include <cstddef>
#include <cstring>
#include <iostream>
#include <string>
#include "bindings.hpp"


#include "network_cfg.hh"

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



    // uint8_t pot_position;
    // uint8_t tcon_config;
    // bool tcon_a, tcon_b, tcon_w;

    // for (int i = 0; i < bindings::kNumNeuronsPerLayer; i++) {
    //     for (int j = 0; j < bindings::kNumWeightsPerNeuron; j++) {
    //         pot_position = bindings::pots[0][i][j].GetPosition();
    //         std::cout << "Layer " << 0 << " Neuron " << i << " Weight " << j << " Position: " << std::to_string(pot_position) << std::endl;
    //     }
    //     pot_position = bindings::bias_pots[0][i].GetPosition();
    //     std::cout << "Layer " << 0 << " Neuron " << i << " Bias Position: " << std::to_string(pot_position) << std::endl;
    //     bindings::bias_pots[0][i].GetTerminalConnections(&tcon_a, &tcon_b, &tcon_w);
    //     std::cout << "Layer " << 0 << " Neuron " << i << " Bias Terminal Connections: " << std::to_string(tcon_a) << " " << std::to_string(tcon_b) << " " << std::to_string(tcon_w) << std::endl;
 
    //     pot_position  = bindings::fb_pots[0][i].GetPosition();
    //     std::cout << "Layer " << 0 << " Neuron " << i << " Feedback Position: " << std::to_string(pot_position) << std::endl;
    //     bindings::fb_pots[0][i].GetTerminalConnections(&tcon_a, &tcon_b, &tcon_w);
    //     std::cout << "Layer " << 0 << " Neuron " << i << " Feedback Terminal Connections: " << std::to_string(tcon_a) << " " << std::to_string(tcon_b) << " " << std::to_string(tcon_w) << std::endl;
    // }

    // for (int i = 0; i < bindings::kNumNeuronsPerLayerOutput; i++) {
    //     for (int j = 0; j < bindings::kNumWeightsPerNeuron; j++) {
    //         pot_position = bindings::pots[1][i][j].GetPosition();
    //         std::cout << "Layer " << 1  << " Neuron " << i << " Weight " << j << " Position: " << std::to_string(pot_position) << std::endl;
    //     }
    //     pot_position = bindings::bias_pots[1][i].GetPosition();
    //     std::cout << "Layer " << 1  << " Neuron " << i << " Bias Position: " << std::to_string(pot_position) << std::endl;
    //     bindings::bias_pots[1][i].GetTerminalConnections(&tcon_a, &tcon_b, &tcon_w);
    //     std::cout << "Layer " << 1  << " Neuron " << i << " Bias Terminal Connections: " << std::to_string(tcon_a) << " " << std::to_string(tcon_b) << " " << std::to_string(tcon_w) << std::endl;
 
    //     pot_position  = bindings::fb_pots[0][1].GetPosition();
    //     std::cout << "Layer "  << 1 << " Neuron " << i << " Feedback Position: " << std::to_string(pot_position) << std::endl;
    //     bindings::fb_pots[1][i].GetTerminalConnections(&tcon_a, &tcon_b, &tcon_w);
    //     std::cout << "Layer "  << 1 << " Neuron " << i << " Feedback Terminal Connections: " << std::to_string(tcon_a) << " " << std::to_string(tcon_b) << " " << std::to_string(tcon_w) << std::endl;
    // }

    

    // bool light = false;
    // int i = 0;
    // int j = 0;
    // std::string placeholder;


    // std::cout <<"init config" << std::endl;
    // std::cin >> placeholder;
    bool light = false;
    while (1) {
        // for (i = 0; i < 3; i++){
        //     for(j = 0; j < 4; j++){
        //         input_values[i][j] = -1.0f;
        //         std::cout << " i: " << i << " j: " << j << " weight:" << (i <<2) + j  << std::endl;

        //         bindings::analog_output_group_0.SetAndLoadAllVoltages(input_values[0]);
        //         bindings::analog_output_group_1.SetAndLoadAllVoltages(input_values[1]);
        //         bindings::analog_output_group_2.SetAndLoadAllVoltages(input_values[2]);            
        //         std::cin >> placeholder;

        //         input_values[i][j] = 0.0f;
        //     }
        // }

        bindings::red_led.Set(light);

        uint8_t buf[53] = {0};
        // uint8_t check[] = "ANN-E";
        shared::uart::Message<shared::uart::MessageType::Receive> msg{buf};
        bindings::uart_bus.ReceiveBlocking(msg);
        for(int i = 0; i < 12; i++){
            input_values[i/4][i%4] = bytesToFloat(msg.Data() + 5 + i*4);
        }
    
        for(int i = 0; i < 12; i++){
            std::cout << std::to_string (input_values[i/4][i%4]) << std::endl;
        }
    
        bindings::green_led.Set(1);
    
        bindings::analog_output_group_0.SetAndLoadAllVoltages(input_values[0]);
        bindings::analog_output_group_1.SetAndLoadAllVoltages(input_values[1]);
        bindings::analog_output_group_2.SetAndLoadAllVoltages(input_values[2]);

        light = !light;
        bindings::DelayMs(500);        
    }

    return 0;
}