// cubemx includes
#include "gpio.h"
#include "main.h"
#include "dac.h"
#include "i2c.h"
#include "stm32f7xx_hal.h"

// project includes
#include "bindings.h"
#include "mcal/stm32f767/periph/gpio.h"
#include "shared/periph/gpio.h"

#include "shared/periph/dac.h"
#include "mcal/stm32f767/periph/dac.h"

#include "mcal/stm32f767/periph/i2c.h"
#include "shared/periph/i2c.h"



extern "C" {
/**
 * This requires extern since it is not declared in a header, only defined
 * in cubemx/../main.c
 */
void SystemClock_Config();
}
namespace mcal {
using namespace stm32f767::periph;

DigitalOutput indicator{LedPin_GPIO_Port, LedPin_Pin};
DACOutput dac{&hdac, DAC_CHANNEL_2};
I2C i2c{&hi2c1};

}  // namespace mcal

namespace bindings {


shared::periph::DigitalOutput& indicator = mcal::indicator;
shared::periph::DACOutput& dac = mcal::dac;
shared::periph::I2C& i2c = mcal::i2c;


void DelayMS(unsigned int ms) {
    HAL_Delay(ms);
}

void Initialize() {
    SystemClock_Config();
    HAL_Init();
    MX_GPIO_Init();
    MX_DAC_Init();
    MX_I2C1_Init();
    dac.Start();
}

}  // namespace bindings