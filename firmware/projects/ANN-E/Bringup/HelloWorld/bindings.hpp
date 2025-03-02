#pragma once

#include "shared/periph/analog_output.hpp"
#include "shared/periph/gpio.hpp"
#include "shared/periph/pwm.hpp"

namespace bindings {

extern shared::periph::DigitalOutput& red_led;
extern shared::periph::DigitalOutput& heartbeat;


extern void DelayMs(uint32_t ms);
extern void Init();

}  // namespace bindings