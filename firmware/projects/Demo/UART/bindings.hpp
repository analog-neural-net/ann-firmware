#pragma once

#include "shared/periph/gpio.hpp"
#include "shared/periph/uart.hpp"

namespace bindings {

extern shared::periph::DigitalOutput& indicator;
extern shared::periph::UartBus& uart_bus;

extern void DelayMS(unsigned int ms);
extern void Initialize();

}  // namespace bindings