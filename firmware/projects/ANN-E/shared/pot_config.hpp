#pragma once

#include <cstdint>

namespace app {

struct PotConfig {
    uint8_t position;
    bool terminal_connect_a;
    bool terminal_connect_b;
    bool terminal_connect_w;
};

}  // namespace app
