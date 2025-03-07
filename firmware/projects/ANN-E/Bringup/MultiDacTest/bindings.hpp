#pragma once

#include "shared/periph/analog_input.hpp"
#include "shared/periph/analog_output.hpp"
#include "shared/periph/gpio.hpp"
#include "shared/periph/pwm.hpp"
#include "shared/periph/i2c.hpp"
#include "shared/device/dac.hpp"

namespace bindings {

constexpr uint8_t kNumAnalogOutputsPerDevice = 4;
constexpr uint8_t kNumAnalogOutputDevices = 3;
constexpr uint8_t kNumi2cBuses = 3;
constexpr uint8_t kNumi2cChannelsPerBus = 8;

extern shared::periph::DigitalOutput& red_led;
extern shared::periph::DigitalOutput& green_led;
extern shared::periph::DigitalOutput& blue_led;

extern shared::periph::I2CBus& i2c1;
extern shared::periph::I2CBus& i2c1A;

extern shared::periph::I2CBus& i2c2;
extern shared::periph::I2CBus& i2c3;


extern shared::device::DigitalAnalogConverterGroup<kNumAnalogOutputsPerDevice>&
    analog_output_group;

extern void DelayMs(uint32_t ms);
extern void Init();

}  // namespace bindings