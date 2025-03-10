#include <unistd.h>

#include <iostream>

#include "../../bindings.h"
#include "mcal/cli/periph/gpio.hpp"
#include "mcal/cli/periph/i2c.hpp"
#include "shared/periph/gpio.hpp"
#include "shared/periph/i2c.hpp"

namespace mcal {
using namespace cli::periph;

I2CBus i2c_bus1(1);
DigitalOutput indicator("Indicator");

}  // namespace mcal

namespace bindings {

shared::periph::DigitalOutput& indicator = mcal::indicator;
shared::periph::I2CBus& i2c_bus1 = mcal::i2c_bus1;

void DelayMS(unsigned int ms) {
    usleep(ms * 1000);
}

void Initialize() {
    std::cout << "Initializing the CLI..." << std::endl;
}

}  // namespace bindings