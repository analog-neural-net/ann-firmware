#pragma once

#include "shared/periph/analog_input.hpp"
#include "shared/periph/analog_output.hpp"
#include "shared/periph/gpio.hpp"
#include "shared/periph/pwm.hpp"
#include "shared/periph/i2c.hpp"

namespace bindings {

constexpr uint8_t kNumAnalogInputs = 10;

extern shared::periph::DigitalOutput& red_led;
extern shared::periph::DigitalOutput& green_led;
extern shared::periph::DigitalOutput& blue_led;


extern shared::periph::AnalogInput& analog_input_0;
extern shared::periph::AnalogInput& analog_input_1;
extern shared::periph::AnalogInput& analog_input_2;
extern shared::periph::AnalogInput& analog_input_3;
extern shared::periph::AnalogInput& analog_input_4;
extern shared::periph::AnalogInput& analog_input_5;
extern shared::periph::AnalogInput& analog_input_6;
extern shared::periph::AnalogInput& analog_input_7;
extern shared::periph::AnalogInput& analog_input_8;
extern shared::periph::AnalogInput& analog_input_9;


extern void DelayMs(uint32_t ms);
extern void Init();

}  // namespace bindings