#pragma once

#include <cstdint>
#include <vector>

#include "neuron.hpp"
#include "pot_config.hpp"

namespace anne {

template <size_t num_outputs, size_t num_inputs>
class Layer {
public:
    Layer(uint8_t layer_id, Neuron<num_inputs> neurons[num_outputs])
        : layer_id_(layer_id), neurons_(neurons) {}
    ~Layer() = default;

    uint8_t LayerId() const {
        return layer_id_;
    }

    void SetWeights(PotConfig weight_configs[num_outputs][num_inputs]) {
        for (size_t i = 0; i < num_outputs; i++) {
            neurons_[i].SetWeights(weight_configs[i]);
        }
    }

    void SetBiases(PotConfig bias_configs[num_outputs]) {
        for (size_t i = 0; i < num_outputs; i++) {
            neurons_[i].SetBias(bias_configs[i]);
        }
    }

    void SetFeedbacks(PotConfig feedback_configs[num_outputs]) {
        for (size_t i = 0; i < num_outputs; i++) {
            neurons_[i].SetFeedback(feedback_configs[i]);
        }
    }

    Neuron<num_inputs>& operator[](size_t index) {
        return neurons_[index];
    }

private:
    uint8_t layer_id_;
    Neuron<num_inputs> neurons_[num_outputs];
};

}  // namespace anne
