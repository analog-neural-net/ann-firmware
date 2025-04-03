#pragma once

#include "shared/util/device.hpp"

namespace shared::device {
    class CurrentSensor : public shared::util::Device {
        public:
            virtual float ReadCurrent() = 0;
        };
}
