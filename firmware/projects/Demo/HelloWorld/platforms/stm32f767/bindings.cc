// cubemx includes
#include "gpio.h"
#include "main.h"
#include "stm32f7xx_hal.h"
#include "usart.h"

// project includes
#include "../../bindings.hpp"
#include "mcal/stm32f767/periph/gpio.hpp"
#include "mcal/stm32f767/util/stdio_retarget.h"
#include "shared/periph/gpio.hpp"

extern "C" {
void SystemClock_Config();
}
namespace mcal {
using namespace stm32f767::periph;

DigitalOutput indicator{LedPin_GPIO_Port, LedPin_Pin};
UART_HandleTypeDef* debug_uart = &huart3;

}  // namespace mcal

namespace bindings {

shared::periph::DigitalOutput& indicator = mcal::indicator;

void DelayMs(unsigned int ms) {
    HAL_Delay(ms);
}

void Initialize() {
    SystemClock_Config();
    HAL_Init();
    MX_GPIO_Init();
    MX_USART3_UART_Init();
    SetDebugUART(mcal::debug_uart);
}

}  // namespace bindings