// cubemx includes
#include "gpio.h"
#include "main.h"
#include "stm32f7xx_hal.h"
#include "usart.h"

// project includes
#include "../../bindings.hpp"
#include "mcal/stm32f767/periph/gpio.hpp"
#include "mcal/stm32f767/periph/uart.hpp"
#include "mcal/stm32f767/util/stdio_retarget.h"
#include "shared/periph/gpio.hpp"
#include "shared/periph/uart.hpp"

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
UART_HandleTypeDef* debug_uart = &huart3;
UartBus uart_bus{&huart3};

}  // namespace mcal

namespace bindings {

shared::periph::DigitalOutput& indicator = mcal::indicator;
shared::periph::UartBus& uart_bus = mcal::uart_bus;

void DelayMS(unsigned int ms) {
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