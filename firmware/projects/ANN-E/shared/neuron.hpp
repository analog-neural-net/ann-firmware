#pragma once

#include <cstdint>

#include "pot_config.hpp"
#include "shared/device/digital_pot.hpp"

namespace app {

template <size_t num_inputs>
class Neuron {
public:
    Neuron(
        uint8_t layer_id, uint8_t neuron_id,
        shared::device::DigitalPotentiometer<uint8_t> weight_pots[num_inputs],
        shared::device::DigitalPotentiometer<uint8_t> bias_pot,
        shared::device::DigitalPotentiometer<uint8_t> feedback_pot)
        : layer_id_(layer_id),
          neuron_id_(neuron_id),
          weight_pots_(weight_pots),
          bias_pot_(bias_pot),
          feedback_pot_(feedback_pot) {}
    ~Neuron() = default;

    uint8_t LayerId() const {
        return layer_id_;
    }

    uint8_t NeuronId() const {
        return neuron_id_;
    }

    void SetWeights(PotConfig weight_configs[num_inputs]) {
        for (size_t i = 0; i < num_inputs; i++) {
            SetWeight(i, weight_configs[i]);
        }
    }

    void SetBias(PotConfig bias_config) {
        bias_pot_.SetPosition(bias_config.position);
        bias_pot_.SetTerminalConnections(bias_config.terminal_connect_a,
                                         bias_config.terminal_connect_b,
                                         bias_config.terminal_connect_w);
    }

    void SetFeedback(PotConfig feedback_config) {
        feedback_pot_.SetPosition(feedback_config.position);
        feedback_pot_.SetTerminalConnections(
            feedback_config.terminal_connect_a,
            feedback_config.terminal_connect_b,
            feedback_config.terminal_connect_w);
    }

private:
    void SetWeight(uint8_t index, PotConfig& config) {
        weight_pots_[index].SetPosition(config.position);
        weight_pots_[index].SetTerminalConnections(config.terminal_connect_a,
                                                   config.terminal_connect_b,
                                                   config.terminal_connect_w);
    }

    uint8_t layer_id_;
    uint8_t neuron_id_;

    shared::device::DigitalPotentiometer<uint8_t> weight_pots_[num_inputs];
    shared::device::DigitalPotentiometer<uint8_t> bias_pot_;
    shared::device::DigitalPotentiometer<uint8_t> feedback_pot_;
};

}  // namespace app
