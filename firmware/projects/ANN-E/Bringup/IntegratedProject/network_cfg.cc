#include "network_cfg.hpp"
#include "bindings.hpp"
#include "audio_model_cfg.hpp"
#include "visual_model_cfg.hpp"


void program_model(model loaded_model) {
    auto neurons_pot_positions = loaded_model==model::AUDIO ? audio_model::neurons_pot_positions : visual_model::neurons_pot_positions;
    auto neurons_pot_positions_2 = loaded_model==model::AUDIO ? audio_model::neurons_pot_positions_2 : visual_model::neurons_pot_positions_2;

    auto bias_pot_positions = loaded_model==model::AUDIO ? audio_model::bias_pot_positions : visual_model::bias_pot_positions;
    auto bias_pot_positions_2 = loaded_model==model::AUDIO ? audio_model::bias_pot_positions_2 : visual_model::bias_pot_positions_2;
    
    auto feedback_pot_positions = loaded_model==model::AUDIO ? audio_model::feedback_pot_positions : visual_model::feedback_pot_positions;
    auto feedback_pot_positions_2 = loaded_model==model::AUDIO ? audio_model::feedback_pot_positions_2 : visual_model::feedback_pot_positions_2;

    auto neuron_tcona_settings = loaded_model==model::AUDIO ? audio_model::neuron_tcona_settings : visual_model::neuron_tcona_settings;
    auto neuron_tconb_settings = loaded_model==model::AUDIO ? audio_model::neuron_tconb_settings : visual_model::neuron_tconb_settings;
    auto neuron_tconw_settings = loaded_model==model::AUDIO ? audio_model::neuron_tconw_settings : visual_model::neuron_tconw_settings;

    auto neuron_tcona_settings_2 = loaded_model==model::AUDIO ? audio_model::neuron_tcona_settings_2 : visual_model::neuron_tcona_settings_2;
    auto neuron_tconb_settings_2 = loaded_model==model::AUDIO ? audio_model::neuron_tconb_settings_2 : visual_model::neuron_tconb_settings_2;
    auto neuron_tconw_settings_2 = loaded_model==model::AUDIO ? audio_model::neuron_tconw_settings_2 : visual_model::neuron_tconw_settings_2;

    auto bias_tcona_settings = loaded_model==model::AUDIO ? audio_model::bias_tcona_settings : visual_model::bias_tcona_settings;
    auto bias_tconb_settings = loaded_model==model::AUDIO ? audio_model::bias_tconb_settings : visual_model::bias_tconb_settings;
    auto bias_tconw_settings = loaded_model==model::AUDIO ? audio_model::bias_tconw_settings : visual_model::bias_tconw_settings;
    
    auto bias_tcona_settings_2 = loaded_model==model::AUDIO ? audio_model::bias_tcona_settings_2 : visual_model::bias_tcona_settings_2;
    auto bias_tconb_settings_2 = loaded_model==model::AUDIO ? audio_model::bias_tconb_settings_2 : visual_model::bias_tconb_settings_2;
    auto bias_tconw_settings_2 = loaded_model==model::AUDIO ? audio_model::bias_tconw_settings_2 : visual_model::bias_tconw_settings_2;
    
    auto feedback_tcona_settings = loaded_model==model::AUDIO ? audio_model::feedback_tcona_settings : visual_model::feedback_tcona_settings;
    auto feedback_tconb_settings = loaded_model==model::AUDIO ? audio_model::feedback_tconb_settings : visual_model::feedback_tconb_settings;
    auto feedback_tconw_settings = loaded_model==model::AUDIO ? audio_model::feedback_tconw_settings : visual_model::feedback_tconw_settings;

    auto feedback_tcona_settings_2 = loaded_model==model::AUDIO ? audio_model::feedback_tcona_settings_2 : visual_model::feedback_tcona_settings_2;
    auto feedback_tconb_settings_2 = loaded_model==model::AUDIO ? audio_model::feedback_tconb_settings_2 : visual_model::feedback_tconb_settings_2;
    auto feedback_tconw_settings_2 = loaded_model==model::AUDIO ? audio_model::feedback_tconw_settings_2 : visual_model::feedback_tconw_settings_2;

    for (int i = 0; i < bindings::kNumNeuronsPerLayer; i++) {
    for (int j = 0; j < bindings::kNumWeightsPerNeuron; j++) {
        bindings::pots[0][i][j].SetPosition(neurons_pot_positions[i][j]);
        bindings::DelayMs(10);
        bindings::pots[0][i][j].SetTerminalConnections(
            neuron_tcona_settings[i][j],
            neuron_tconb_settings[i][j],
            neuron_tconw_settings[i][j]
        );
    }
    bindings::bias_pots[0][i].SetPosition(bias_pot_positions[i]);
    bindings::bias_pots[0][i].SetTerminalConnections(
        bias_tcona_settings[i],
        bias_tconb_settings[i],
        bias_tconw_settings[i]
    );
    bindings::fb_pots[0][i].SetPosition(feedback_pot_positions[i]);
    bindings::fb_pots[0][i].SetTerminalConnections(
        feedback_tcona_settings[i],
        feedback_tconb_settings[i],
        feedback_tconw_settings[i]
    );
}

for (int i = 0; i < bindings::kNumNeuronsPerLayerOutput; i++) {
    for (int j = 0; j < bindings::kNumWeightsPerNeuron; j++) {
        bindings::pots[1][i][j].SetPosition(neurons_pot_positions_2[i][j]);
        bindings::DelayMs(10);
        bindings::pots[1][i][j].SetTerminalConnections(
            neuron_tcona_settings_2[i][j],
            neuron_tconb_settings_2[i][j],
            neuron_tconw_settings_2[i][j]
        );
    }
    bindings::bias_pots[1][i].SetPosition(bias_pot_positions_2[i]);
    bindings::bias_pots[1][i].SetTerminalConnections(
        bias_tcona_settings_2[i],
        bias_tconb_settings_2[i],
        bias_tconw_settings_2[i]
    );
    bindings::fb_pots[1][i].SetPosition(feedback_pot_positions_2[i]);
    bindings::fb_pots[1][i].SetTerminalConnections(
        feedback_tcona_settings_2[i],
        feedback_tconb_settings_2[i],
        feedback_tconw_settings_2[i]
    );
}
}