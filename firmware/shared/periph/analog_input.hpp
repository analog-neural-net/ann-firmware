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

class AnalogInputDualEnded final : public AnalogInput {
public:
    AnalogInputDualEnded(AnalogInput& negative_ref, AnalogInput& positive_ref)
        : negative_ref_(negative_ref), positive_ref_(positive_ref) {}
    float ReadVoltage() override {
        return positive_ref_.ReadVoltage() - negative_ref_.ReadVoltage();
    }

private:
    AnalogInput& negative_ref_;
    AnalogInput& positive_ref_;
};

}  // namespace shared::periph