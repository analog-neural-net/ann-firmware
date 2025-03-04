#pragma once

#include "shared/periph/gpio.hpp"
#include "shared/periph/i2c.hpp"

namespace bindings {

extern shared::periph::I2CBus& i2c_bus1A;
extern shared::periph::I2CBus& i2c_bus1B;

extern void DelayMS(unsigned int ms);
extern void Initialize();

}  // namespace bindings