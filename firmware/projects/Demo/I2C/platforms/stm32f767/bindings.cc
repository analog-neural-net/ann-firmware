/// @author Blake Freer
/// @date 2023-12-25

// cubemx files
#include "gpio.h"
#include "i2c.h"
#include "main.h"

// fw includes
#include "../../bindings.hpp"
#include "mcal/stm32f767/periph/gpio.hpp"
#include "mcal/stm32f767/periph/i2c.hpp"
#include "shared/periph/gpio.hpp"
#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_i2c.h"

extern "C" {
/**
 * This requires extern since it is not declared in a header, only defined
 * in cubemx/../main.c
 */
void SystemClock_Config();
}

namespace mcal {
using namespace stm32f767::periph;

DigitalInput button_di{ButtonPin_GPIO_Port, ButtonPin_Pin};
DigitalOutput indicator{LedPin_GPIO_Port, LedPin_Pin};

I2C i2c2{&hi2c2};

}  // namespace mcal

namespace bindings {
shared::periph::DigitalInput& button_di = mcal::button_di;
shared::periph::DigitalOutput& indicator = mcal::indicator;

shared::periph::I2CBus& i2c_bus2 = mcal::i2c2;

void DelayMS(unsigned int ms) {
    HAL_Delay(ms * 1000);
}

void Initialize() {
    SystemClock_Config();
    HAL_Init();
    HAL_I2C_Init(&hi2c2);
    MX_GPIO_Init();
}

}  // namespace bindings
