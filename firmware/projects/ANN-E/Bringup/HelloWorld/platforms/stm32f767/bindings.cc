/// @author Hydar Zartash
/// @date 2025-03-01

// cubemx files
#include "usart.h"
#include "main.h"
#include "gpio.h"

// fw includes
#include "../../bindings.hpp"
#include "mcal/stm32f767/util/stdio_retarget.h"
#include "mcal/stm32f767/periph/gpio.hpp"

extern "C" {
/**
 * This requires extern since it is not declared in a header, only defined
 * in cubemx/../main.c
 */
void SystemClock_Config();
}

namespace mcal {
using namespace stm32f767::periph;
DigitalOutput heartbeat(UC_Heartbeat_GPIO_Port, UC_Heartbeat_Pin);
DigitalOutput red_led(red_led_GPIO_Port, red_led_Pin);

UART_HandleTypeDef* debug_uart = &huart3;
}  // namespace mcal



namespace bindings {
shared::periph::DigitalOutput& heartbeat = mcal::heartbeat;
shared::periph::DigitalOutput& red_led = mcal::red_led;

void Init() {
    SystemClock_Config();
    HAL_Init();
    MX_GPIO_Init();
    MX_USART3_UART_Init();

    SetDebugUART(mcal::debug_uart);
}

void DelayMs(uint32_t ms)
{
    HAL_Delay(ms);
}

}  // namespace bindings
