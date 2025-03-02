#pragma once

#include "shared/periph/analog_input.hpp"
#include "shared/periph/analog_output.hpp"
#include "shared/periph/gpio.hpp"
#include "shared/periph/pwm.hpp"
#include "shared/periph/i2c.hpp"

namespace bindings {

constexpr uint8_t kNumAnalogOutputs = 4;

extern shared::periph::DigitalOutput& red_led;
extern shared::periph::DigitalOutput& green_led;
extern shared::periph::DigitalOutput& blue_led;

extern shared::periph::I2CBus& i2c_bus2;

extern shared::periph::AnalogOutputGroup<kNumAnalogOutputs>&
    analog_output_group;

extern void DelayMs(uint32_t ms);
extern void Init();

}  // namespace bindings