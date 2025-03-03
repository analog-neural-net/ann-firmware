#pragma once

#include <cstdint>
#include <vector>

#include "layer.hpp"
#include "shared/periph/analog_input.hpp"
#include "shared/periph/analog_output.hpp"

namespace app {

template <size_t num_layers, size_t num_outputs, size_t num_inputs>
class Network {
public:
    Network(Layer<num_inputs, num_outputs> layers[num_layers],
            shared::periph::AnalogOutputGroup<num_outputs>& analog_output_group,
            shared::periph::AnalogInputGroup<num_inputs>& analog_input_group,
            bool digital_softmax = false)
        : layers_(layers),
          analog_output_group_(analog_output_group),
          analog_input_group_(analog_input_group),
          digital_softmax_(digital_softmax) {}
    ~Network() = default;

    void SetWeights(
        PotConfig weight_configs[num_layers][num_outputs][num_inputs]) {
        for (size_t i = 0; i < num_layers; i++) {
            layers_[i].SetWeights(weight_configs[i]);
        }
    }

    void SetBiases(PotConfig bias_configs[num_layers][num_outputs]) {
        for (size_t i = 0; i < num_layers; i++) {
            layers_[i].SetBiases(bias_configs[i]);
        }
    }

    void SetFeedbacks(PotConfig feedback_configs[num_layers][num_outputs]) {
        for (size_t i = 0; i < num_layers; i++) {
            layers_[i].SetFeedbacks(feedback_configs[i]);
        }
    }

    void SetDigitalSoftmax(bool digital_softmax) {
        digital_softmax_ = digital_softmax;
    }

    uint8_t PerformInference(float inputs[num_inputs],
                             float outputs[num_outputs]) {
        analog_output_group_.SetAndLoadAllVoltages(inputs);
        analog_input_group_.ReadVoltages(inputs);

        if (digital_softmax_) {
            Softmax(inputs, outputs);
        } else {
            std::memcpy(outputs, inputs, num_outputs * sizeof(float));
        }

        // Return index of maximum output
        size_t max_idx = 0;
        for (size_t i = 1; i < num_outputs; i++) {
            if (outputs[i] > outputs[max_idx]) {
                max_idx = i;
            }
        }

        return max_idx;
    }

private:
    void Softmax(const float (&x)[num_outputs], float (&y)[num_outputs]) {
        // Find max value
        float max_val = x[0];
        for (size_t i = 1; i < num_outputs; i++) {
            if (x[i] > max_val) {
                max_val = x[i];
            }
        }

        // Compute exp(x - max) and sum
        float sum = 0;
        for (size_t i = 0; i < num_outputs; i++) {
            y[i] = exp(x[i] - max_val);
            sum += y[i];
        }

        // Normalize
        for (size_t i = 0; i < num_outputs; i++) {
            y[i] /= sum;
        }
    }

    Layer<num_inputs, num_outputs> layers_[num_layers];
    shared::periph::AnalogOutputGroup<num_outputs>& analog_output_group_;
    shared::periph::AnalogInputGroup<num_inputs>& analog_input_group_;
    bool digital_softmax_;
};

}  // namespace app
