#pragma once

#include <cstdint>
#include "bindings.hpp"


namespace test_cfg {
    constexpr uint16_t test_size = 10000;
    constexpr uint16_t inputs = 12;
    constexpr uint16_t outputs = 10;

    constexpr uint16_t propogation_delay = 10;

    extern uint16_t confusion_matrix[outputs][outputs];
    extern float data[test_size][bindings::kNumAnalogInputs + 1];
}

