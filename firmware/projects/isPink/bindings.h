#pragma once

#include "shared/periph/gpio.h"
#include "shared/periph/dac.h"

namespace bindings {

extern shared::periph::DigitalOutput& indicator;
extern shared::periph::DigitalInput& button;
extern shared::periph::DACOutput& dac;

extern void DelayMS(unsigned int ms);
extern void Initialize();

}  // namespace bindings