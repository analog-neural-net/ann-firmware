
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
#include "test_cfg.hpp"

char temp;

float input_values[bindings::kInputLayerDim] = 
    {0.0, 0.0, 0.0, 0.0,0.0, 0.0, 0.0, 0.0,0.0, 0.0, 0.0, 0.0};

std::array<float, 10> output_values = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

auto softmax = [](float* values, size_t size) {
    float max_val = *std::max_element(values, values + size);
    float sum = 0.0f;

    for (size_t i = 0; i < size; ++i) {
        values[i] = std::exp(values[i] - max_val);
        sum += values[i];
    }

    for (size_t i = 0; i < size; ++i) {
        values[i] /= sum;
    }
};

auto max_idx = [](std::array<float, 10>& raw) {
    return std::max_element(raw.begin(), raw.end()) - raw.begin();
};

int main() {
    bindings::Init();

    bindings::red_led.Set(1);

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
            input_values[i] = test_cfg::data[test][1 + i];
            // bindings::DelayMs(test_cfg::propogation_delay);
        }

        bindings::dac_channels.SetAndLoadAllVoltages(input_values);

        bindings::DelayMs(1);

        output_values[0] = bindings::analog_input_0.ReadVoltage();
        output_values[1] = bindings::analog_input_1.ReadVoltage();
        output_values[2] = bindings::analog_input_2.ReadVoltage();
        output_values[3] = bindings::analog_input_3.ReadVoltage();
        output_values[4] = bindings::analog_input_4.ReadVoltage();
        output_values[5] = bindings::analog_input_5.ReadVoltage();
        output_values[6] = bindings::analog_input_6.ReadVoltage();
        output_values[7] = bindings::analog_input_7.ReadVoltage();
        output_values[8] = bindings::analog_input_8.ReadVoltage();
        output_values[9] = bindings::analog_input_9.ReadVoltage();

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
    

    while (1) {
        bindings::red_led.Set(light);
        light = !light;
        bindings::DelayMs(500);
    }

    return 0;
}