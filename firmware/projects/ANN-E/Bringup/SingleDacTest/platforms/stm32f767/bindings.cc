/// @author Blake Freer
/// @date 2023-12-25

// cubemx files
#include "gpio.h"
#include "i2c.h"
#include "usart.h"
#include "main.h"

// fw includes
#include "../../bindings.hpp"
#include "mcal/stm32f767/periph/gpio.hpp"
#include "mcal/stm32f767/periph/i2c.hpp"
#include "mcal/stm32f767/util/stdio_retarget.h"
#include "shared/periph/gpio.hpp"
#include "shared/device/mcp/mcp4728.hpp"

extern "C" {
/**
 * This requires extern since it is not declared in a header, only defined
 * in cubemx/../main.c
 */
void SystemClock_Config();
}

namespace mcal {
using namespace stm32f767::periph;

DigitalOutput red_led(red_led_GPIO_Port, red_led_Pin);
DigitalOutput green_led(UC_Heartbeat_GPIO_Port, UC_Heartbeat_Pin);


I2CBus i2c2(&hi2c2);

UART_HandleTypeDef* debug_uart = &huart3;
}  // namespace mcal

namespace devices{
using namespace shared::device::mcp;
    MCP4728 dac(mcal::i2c2, 0x62, 3.3F, 0.F);
}

namespace bindings {
shared::periph::DigitalOutput& red_led = mcal::red_led;
shared::periph::DigitalOutput& green_led = mcal::green_led;

    
shared::periph::I2CBus& i2c_bus2 = mcal::i2c2;

shared::periph::AnalogOutputGroup<4>& analog_output_group = devices::dac;

void Init() {
    SystemClock_Config();
    HAL_Init();
    MX_GPIO_Init();
    MX_USART3_UART_Init();
    MX_I2C2_Init();

    SetDebugUART(mcal::debug_uart);
}

void DelayMs(uint32_t ms)
{
    HAL_Delay(ms);
}

}  // namespace bindings
