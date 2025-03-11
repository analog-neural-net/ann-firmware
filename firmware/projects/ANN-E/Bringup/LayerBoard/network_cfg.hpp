#pragma once

#include "bindings.hpp"


extern uint8_t neurons_pot_positions[4][bindings::kNumWeightsPerNeuron];

extern bool neuron_tcona_settings[4][bindings::kNumWeightsPerNeuron];
extern bool neuron_tconw_settings[4][bindings::kNumWeightsPerNeuron];
extern bool neuron_tconb_settings[4][bindings::kNumWeightsPerNeuron];

extern uint8_t bias_pot_positions[4];

extern bool bias_tcona_settings[4];
extern bool bias_tconw_settings[4];
extern bool bias_tconb_settings[4];

extern uint8_t feedback_pot_positions[4];

extern bool feedback_tcona_settings[4];
extern bool feedback_tconw_settings[4];
extern bool feedback_tconb_settings[4];
