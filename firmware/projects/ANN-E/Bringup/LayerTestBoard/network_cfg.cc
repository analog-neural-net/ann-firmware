#include "network_cfg.hpp"

uint8_t neurons_pot_positions[bindings::kNumNeuronsPerLayer][bindings::kNumWeightsPerNeuron] = {
    {
    13,
    3,
    84,
    240,
    248,
    250,
    12,
    41,
    0,
    209,
    220,
    227,
    },
    {
    251,
    66,
    255,
    7,
    255,
    200,
    212,
    25,
    38,
    255,
    163,
    255,
    },
    {
    3,
    154,
    255,
    28,
    0,
    250,
    184,
    16,
    119,
    233,
    255,
    215,
    },
    {
    213,
    232,
    34,
    251,
    27,
    219,
    217,
    86,
    6,
    31,
    164,
    0,
    },
    };
    
    
    bool neuron_tcona_settings[bindings::kNumNeuronsPerLayer][bindings::kNumWeightsPerNeuron] = {
    {
    false,
    false,
    false,
    true,
    true,
    true,
    false,
    true,
    true,
    true,
    true,
    true,
    },
    {
    true,
    false,
    false,
    false,
    false,
    true,
    true,
    false,
    false,
    false,
    false,
    false,
    },
    {
    false,
    true,
    false,
    false,
    false,
    true,
    true,
    false,
    false,
    true,
    false,
    true,
    },
    {
    true,
    true,
    false,
    true,
    false,
    true,
    true,
    false,
    false,
    false,
    true,
    true,
    },
    };
    
    
    bool neuron_tconw_settings[bindings::kNumNeuronsPerLayer][bindings::kNumWeightsPerNeuron] = {
    {
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    },
    {
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    },
    {
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    },
    {
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    true,
    },
    };
    
    
    bool neuron_tconb_settings[bindings::kNumNeuronsPerLayer][bindings::kNumWeightsPerNeuron] = {
    {
    true,
    true,
    true,
    false,
    false,
    false,
    true,
    false,
    false,
    false,
    false,
    false,
    },
    {
    false,
    true,
    false,
    true,
    false,
    false,
    false,
    true,
    true,
    true,
    true,
    false,
    },
    {
    true,
    false,
    false,
    true,
    true,
    false,
    false,
    true,
    true,
    false,
    false,
    false,
    },
    {
    false,
    false,
    true,
    false,
    true,
    false,
    false,
    true,
    true,
    true,
    false,
    false,
    },
    };
    
    
    uint8_t bias_pot_positions[bindings::kNumNeuronsPerLayer] = {
    8,
    204,
    0,
    161,
    };
    
    
    bool bias_tcona_settings[bindings::kNumNeuronsPerLayer] = {
    true,
    true,
    true,
    true,
    };
    
    
    bool bias_tconw_settings[bindings::kNumNeuronsPerLayer] = {
    true,
    true,
    true,
    true,
    };
    
    
    bool bias_tconb_settings[bindings::kNumNeuronsPerLayer] = {
    false,
    false,
    false,
    false,
    };
    
    
    uint8_t feedback_pot_positions[bindings::kNumNeuronsPerLayer] = {
    229,
    212,
    239,
    217,
    };
    
    
    bool feedback_tcona_settings[bindings::kNumNeuronsPerLayer] = {
    true,
    true,
    true,
    true,
    };
    
    
    bool feedback_tconw_settings[bindings::kNumNeuronsPerLayer] = {
    true,
    true,
    true,
    true,
    };
    
    
    bool feedback_tconb_settings[bindings::kNumNeuronsPerLayer] = {
    false,
    false,
    false,
    false,
    };
    
    
    
    