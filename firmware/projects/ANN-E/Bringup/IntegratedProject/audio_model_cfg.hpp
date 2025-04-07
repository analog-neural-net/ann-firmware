#pragma once

#include "bindings.hpp"

namespace audio_model {
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


extern uint8_t neurons_pot_positions_2[bindings::kNumNeuronsPerLayerOutput][bindings::kNumWeightsPerNeuron];

extern bool neuron_tcona_settings_2[bindings::kNumNeuronsPerLayerOutput][bindings::kNumWeightsPerNeuron];
extern bool neuron_tconw_settings_2[bindings::kNumNeuronsPerLayerOutput][bindings::kNumWeightsPerNeuron];
extern bool neuron_tconb_settings_2[bindings::kNumNeuronsPerLayerOutput][bindings::kNumWeightsPerNeuron];

extern uint8_t bias_pot_positions_2[bindings::kNumNeuronsPerLayerOutput];

extern bool bias_tcona_settings_2[bindings::kNumNeuronsPerLayerOutput];
extern bool bias_tconw_settings_2[bindings::kNumNeuronsPerLayerOutput];
extern bool bias_tconb_settings_2[bindings::kNumNeuronsPerLayerOutput];

extern uint8_t feedback_pot_positions_2[bindings::kNumNeuronsPerLayerOutput];

extern bool feedback_tcona_settings_2[bindings::kNumNeuronsPerLayerOutput];
extern bool feedback_tconw_settings_2[bindings::kNumNeuronsPerLayerOutput];
extern bool feedback_tconb_settings_2[bindings::kNumNeuronsPerLayerOutput];
}