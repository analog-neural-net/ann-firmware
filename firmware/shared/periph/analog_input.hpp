/// @author Samuel Shi
/// @date 2024-11-17
/// Modified from adc.h

#pragma once

#include <cstdint>

#include "shared/util/peripheral.hpp"

namespace shared::periph {

class AnalogInput : public util::Peripheral {
public:
    virtual float ReadVoltage() = 0;
};

template <uint8_t num_channels>
class AnalogInputGroup : public util::Peripheral {
public:
    virtual void ReadVoltages(float voltages[num_channels]) = 0;
};

}  // namespace shared::periph