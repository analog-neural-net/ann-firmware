#pragma once

#include "bindings.hpp"
#include "audio_model_cfg.hpp"
#include "visual_model_cfg.hpp"


enum class model {
    AUDIO,
    VISUAL,
};

void program_model(model _model);
