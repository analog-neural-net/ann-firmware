#pragma once

#include "bindings.hpp"


extern uint8_t neurons_pot_positions[bindings::kNumNeuronsPerLayer][bindings::kNumWeightsPerNeuron];

extern bool neuron_tcona_settings[bindings::kNumNeuronsPerLayer][bindings::kNumWeightsPerNeuron];
extern bool neuron_tconw_settings[bindings::kNumNeuronsPerLayer][bindings::kNumWeightsPerNeuron];
extern bool neuron_tconb_settings[bindings::kNumNeuronsPerLayer][bindings::kNumWeightsPerNeuron];

extern uint8_t bias_pot_positions[bindings::kNumNeuronsPerLayer];

extern bool bias_tcona_settings[bindings::kNumNeuronsPerLayer];
extern bool bias_tconw_settings[bindings::kNumNeuronsPerLayer];
extern bool bias_tconb_settings[bindings::kNumNeuronsPerLayer];

extern uint8_t feedback_pot_positions[bindings::kNumNeuronsPerLayer];

extern bool feedback_tcona_settings[bindings::kNumNeuronsPerLayer];
extern bool feedback_tconw_settings[bindings::kNumNeuronsPerLayer];
extern bool feedback_tconb_settings[bindings::kNumNeuronsPerLayer];
