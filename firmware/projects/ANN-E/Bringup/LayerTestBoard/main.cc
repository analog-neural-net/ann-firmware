
#include <stdio.h>

#include <cstring>
#include <iostream>
#include <string>
#include "bindings.hpp"
#include "network_cfg.hpp"
#include "projects/ANN-E/Bringup/LayerTestBoard/bindings.hpp"

int main() {
    bindings::Init();

    bindings::pots[0][0].SetPosition(6);

    for (int i = 0; i < bindings::kNumNeuronsPerLayer; i++) {
        for (int j = 0; j < bindings::kNumWeightsPerNeuron; j++) {
            bindings::pots[i][j].SetPosition(neurons_pot_positions[i][j]);
            bindings::DelayMs(10);
            bindings::pots[i][j].SetTerminalConnections(
                neuron_tcona_settings[i][j],
                neuron_tconb_settings[i][j],
                neuron_tconw_settings[i][j]
            );
        }
        bindings::bias_pots[i].SetPosition(bias_pot_positions[i]);
        bindings::bias_pots[i].SetTerminalConnections(
            bias_tcona_settings[i],
            bias_tconb_settings[i],
            bias_tconw_settings[i]
        );
        bindings::fb_pots[i].SetPosition(feedback_pot_positions[i]);
        bindings::fb_pots[i].SetTerminalConnections(
            feedback_tcona_settings[i],
            feedback_tconb_settings[i],
            feedback_tconw_settings[i]
        );
    }

    uint8_t pot_position;
    uint8_t tcon_config;
    bool tcon_a, tcon_b, tcon_w;

    for (int i = 0; i < bindings::kNumNeuronsPerLayer; i++) {
    //     for (int j = 0; j < bindings::kNumWeightsPerNeuron; j++) {
    //         pot_position = bindings::pots[i][j].GetPosition();
    //         std::cout << "Neuron " << i << " Weight " << j << " Position: " << std::to_string(pot_position) << std::endl;
    //     }
        pot_position = bindings::bias_pots[i].GetPosition();
        std::cout << "Neuron " << i << " Bias Position: " << std::to_string(pot_position) << std::endl;
        bindings::bias_pots[i].GetTerminalConnections(&tcon_a, &tcon_b, &tcon_w);
        std::cout << "Neuron " << i << " Bias Terminal Connections: " << std::to_string(tcon_a) << " " << std::to_string(tcon_b) << " " << std::to_string(tcon_w) << std::endl;
 
        pot_position  = bindings::fb_pots[i].GetPosition();
        std::cout << "Neuron " << i << " Feedback Position: " << std::to_string(pot_position) << std::endl;
        bindings::fb_pots[i].GetTerminalConnections(&tcon_a, &tcon_b, &tcon_w);
        std::cout << "Neuron " << i << " Feedback Terminal Connections: " << std::to_string(tcon_a) << " " << std::to_string(tcon_b) << " " << std::to_string(tcon_w) << std::endl;
    }

    bool light = false;
    while (1) {
        bindings::red_led.Set(light);
        light = !light;
        bindings::DelayMs(500);        
    }

    return 0;
}