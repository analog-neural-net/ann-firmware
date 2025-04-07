#pragma once

#include "shared/periph/analog_output.hpp"
#include "shared/periph/gpio.hpp"
#include "shared/periph/pwm.hpp"
#include "shared/periph/uart.hpp"

namespace bindings {

extern shared::periph::DigitalOutput& red_led;
extern shared::periph::DigitalOutput& green_led;
extern shared::periph::DigitalOutput& heartbeat;
extern shared::periph::UartBus& uart_bus;

extern void DelayMs(uint32_t ms);
extern void Init();

}  // namespace bindings