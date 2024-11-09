/// @author Hydar Zartash
/// @date 2024-11-06

#pragma once

#include <cstdint>

#include "shared/util/peripheral.h"

namespace shared::periph {

class DACOutput : public util::Peripheral {
public:
    virtual void Start() = 0;
    virtual void Set(float value) = 0;
    virtual float Get() = 0;
    virtual void Stop() = 0;
};

}  // namespace shared::periph
