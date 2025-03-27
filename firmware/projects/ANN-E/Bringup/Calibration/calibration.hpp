#pragma once
#include "bindings.hpp"

namespace calibration {

    enum class layer {
        middle,
        output
    };


    extern float StmAdcToANNVoltage(float adc_reading); 
    extern float middleLayerWeights[bindings::kNumNeuronsPerLayer][bindings::kNumWeightsPerNeuron];
    extern float outputLayerWeights[bindings::kNumNeuronsPerLayerOutput][bindings::kNumWeightsPerNeuron];
    extern void calibrateWeight(uint8_t layer, uint8_t neuron, uint8_t weight);
    extern void configureInputLayer(uint8_t layer, uint8_t neuron, uint8_t weight);
    extern void OpenAllTerminals();
    extern void EnablePassThrough(uint8_t layer, uint8_t neuron, uint8_t weight);
    extern void DisablePassThrough(uint8_t layer, uint8_t neuron, uint8_t weight);
    extern void configureInputLayer(uint8_t layer, uint8_t neuron, uint8_t weight);

    float getIdealWeight ( uint8_t layer, uint8_t neuron, uint8_t weight);
    shared::periph::AnalogInput* get_measuring_channel(uint8_t layer, uint8_t neuron, uint8_t weight);
}
