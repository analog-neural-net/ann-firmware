
#include <stdio.h>
#include <sys/_stdint.h>

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <string>

#include "bindings.hpp"
#include "network_cfg.hpp"
#include "projects/ANN-E/Bringup/Calibration/calibration.hpp"
#include "test_cfg.hpp"
#include "calibration.hpp"

float output_values[10];

int main(){
    bindings::Init();

    bindings::green_led.Set(1);
    bindings::red_led.Set(1);
    calibration::OpenAllTerminals();


    
    for(int i = 0; i < bindings::kNumNeuronsPerLayer; i++){
        for(int j = 0; j < bindings::kNumWeightsPerNeuron; j++){
            calibration::calibrateWeight(0, i, j);
        }
        std::cout << std::endl;
    }
    for (int i = 0; i < bindings::kNumNeuronsPerLayerOutput; i++) {
        for (int j = 0; j < bindings::kNumWeightsPerNeuron; j++) {
            calibration::calibrateWeight(1, i, j);
        }
        std::cout << std::endl;
    }
    calibration::calibrateOutputLayerBiases();

    for (int i = 0; i < bindings::kNumNeuronsPerLayer; i++) {
        for (int j = 0; j < bindings::kNumWeightsPerNeuron; j++) {
            bindings::pots[0][i][j].SetPosition(neurons_pot_positions[i][j]);
            bindings::DelayMs(10);
            bindings::pots[0][i][j].SetTerminalConnections(
                neuron_tcona_settings[i][j], neuron_tconb_settings[i][j],
                neuron_tconw_settings[i][j]);
        }
        bindings::bias_pots[0][i].SetPosition(bias_pot_positions[i]);
        bindings::bias_pots[0][i].SetTerminalConnections(
            bias_tcona_settings[i], bias_tconb_settings[i],
            bias_tconw_settings[i]);
        bindings::fb_pots[0][i].SetPosition(feedback_pot_positions[i]);
        bindings::fb_pots[0][i].SetTerminalConnections(
            feedback_tcona_settings[i], feedback_tconb_settings[i],
            feedback_tconw_settings[i]);
    }

    for (int i = 0; i < bindings::kNumNeuronsPerLayerOutput; i++) {
        for (int j = 0; j < bindings::kNumWeightsPerNeuron; j++) {
            bindings::pots[1][i][j].SetPosition(neurons_pot_positions_2[i][j]);
            bindings::DelayMs(10);
            bindings::pots[1][i][j].SetTerminalConnections(
                neuron_tcona_settings_2[i][j], neuron_tconb_settings_2[i][j],
                neuron_tconw_settings_2[i][j]);
        }
        bindings::bias_pots[1][i].SetPosition(bias_pot_positions_2[i]);
        bindings::bias_pots[1][i].SetTerminalConnections(
            bias_tcona_settings_2[i], bias_tconb_settings_2[i],
            bias_tconw_settings_2[i]);
        bindings::fb_pots[1][i].SetPosition(feedback_pot_positions_2[i]);
        bindings::fb_pots[1][i].SetTerminalConnections(
            feedback_tcona_settings_2[i], feedback_tconb_settings_2[i],
            feedback_tconw_settings_2[i]);
    }

    uint32_t start_time = bindings::GetTimeMs();

    bool light = false;

    uint8_t buf[5] = {};
    bindings::red_led.Set(light);
    int test;
    for (test = 0; test < test_cfg::test_size; test++) {
        // shared::uart::Message<shared::uart::MessageType::Receive> msg{buf};
        // bindings::uart_bus.ReceiveBlocking(msg);

        for (int i = 0; i < 12; i++) {
            input_values[i / 4][i % 4] = test_cfg::data[test][1 + i];
            // bindings::DelayMs(test_cfg::propogation_delay);
        }

        bindings::analog_output_group_0.SetAndLoadAllVoltages(input_values[0]);
        bindings::analog_output_group_1.SetAndLoadAllVoltages(input_values[1]);
        bindings::analog_output_group_2.SetAndLoadAllVoltages(input_values[2]);

        bindings::DelayMs(1);

        output_values[0] = bindings::adc_channels[0]->ReadVoltage();
        output_values[1] = bindings::adc_channels[1]->ReadVoltage();
        output_values[2] = bindings::adc_channels[2]->ReadVoltage();
        output_values[3] = bindings::adc_channels[3]->ReadVoltage();
        output_values[4] = bindings::adc_channels[4]->ReadVoltage();
        output_values[5] = bindings::adc_channels[5]->ReadVoltage();
        output_values[6] = bindings::adc_channels[6]->ReadVoltage();
        output_values[7] = bindings::adc_channels[7]->ReadVoltage();
        output_values[8] = bindings::adc_channels[8]->ReadVoltage();
        output_values[9] = bindings::adc_channels[9]->ReadVoltage();

        // std::cout << "Output Values: " << output_values[0] << " ";
        int max = 0;
        for (int i = 1; i < 10; i++) {
            // std::cout << output_values[i] << " ";
            max = output_values[i] > output_values[max] ? i : max;
        }
        // row is actual, column is guess
        test_cfg::confusion_matrix[static_cast<int>(test_cfg::data[test][0])]
                                  [max]++;

        // std::cout << max << std::endl;
    }

    uint32_t runtime = bindings::GetTimeMs() - start_time;
    std::cout << std::endl;
    for (int row = 0; row < 10; row++) {
        for (int col = 0; col < 10; col++) {
            std::cout << std::setw(8) << test_cfg::confusion_matrix[row][col];
        }
        std::cout << std::endl;
    }

    for (int digit = 0; digit < 10; digit++) {
        int sum = 0;
        for (int guess = 0; guess < 10; guess++) {
            sum += test_cfg::confusion_matrix[digit][guess];
        }
        std::cout << "Digit: accuracy: " << digit << " Total: "
                  << 100.f * (float)test_cfg::confusion_matrix[digit][digit] /
                         (float)sum
                  << std::endl;
    }
    int corrects = 0;
    for (int i = 0; i < 10; i++) {
        corrects += test_cfg::confusion_matrix[i][i];
    }

    std::cout << "Total Accuracy: " << 100.f * (float)corrects / (float)test
              << std::endl;
    std::cout << "Total Time: " << runtime << "ms" << std::endl;
    bindings::green_led.Set(1);

    light = !light;
    bindings::DelayMs(500);

    while(1){
        bindings::red_led.Set(1);
        bindings::green_led.Set(0);
        bindings::DelayMs(500);
        bindings::red_led.Set(0);
        bindings::green_led.Set(1);
        bindings::DelayMs(500);
    }
    return 0;
}
