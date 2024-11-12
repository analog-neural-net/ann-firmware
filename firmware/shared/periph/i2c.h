/// @author Hydar Zart
/// @date 2024-11-06

#pragma once

#include <cstdint>
#include "shared/util/peripheral.h"

namespace shared::periph {

class I2C : public util::Peripheral {
public:
    virtual void Write(uint8_t address, uint8_t* data, uint8_t length) = 0;
    virtual void Read(uint8_t address, uint8_t* data, uint8_t length) = 0;
};

}  // namespace shared::periph
