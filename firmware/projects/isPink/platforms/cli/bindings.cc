#include <unistd.h>

#include <iostream>

#include "../../bindings.h"
#include "mcal/cli/periph/gpio.h"
#include "shared/periph/gpio.h"

namespace mcal {

cli::periph::DigitalOutput indicator{"Indicator"};
cli::periph::DigitalInput button{"Button"};


}  // namespace mcal

namespace bindings {

shared::periph::DigitalOutput& indicator = mcal::indicator;
shared::periph::DigitalInput& button = mcal::button;

void DelayMS(unsigned int ms) {
    usleep(ms * 1000);
}

void Initialize() {
    std::cout << "Initializing the CLI..." << std::endl;
}

}  // namespace bindings