#pragma once

#include "shared/periph/gpio.hpp"
#include "shared/periph/i2c.hpp"

namespace bindings {

extern shared::periph::DigitalInput& button_di;
extern shared::periph::DigitalOutput& indicator_do;
extern shared::periph::I2CBus& i2c2;

extern void Initialize();

}  // namespace bindings