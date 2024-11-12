#pragma once

#include "shared/periph/gpio.h"
#include "shared/periph/dac.h"
#include "shared/periph/i2c.h"

namespace bindings {

extern shared::periph::DigitalOutput& indicator;
extern shared::periph::DACOutput& dac;
extern shared::periph::I2C& i2c;

extern void DelayMS(unsigned int ms);
extern void Initialize();

}  // namespace bindings