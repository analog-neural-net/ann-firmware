// cubemx includes
#include "gpio.h"
#include "main.h"
#include "mcal/stm32f767/periph/i2c.hpp"
#include "stm32f7xx_hal.h"
#include "i2c.h"
#include "usart.h"

// project includes
#include "../../bindings.hpp"
#include "mcal/stm32f767/periph/gpio.hpp"
#include "mcal/stm32f767/util/stdio_retarget.h"
#include "shared/periph/gpio.hpp"

extern "C" {
/**
 * This requires extern since it is not declared in a header, only defined
 * in cubemx/../main.c
 */
void SystemClock_Config();
}
namespace mcal {
using namespace stm32f767::periph;

DigitalInput button_0(input_button_0_GPIO_Port, input_button_0_Pin);
DigitalInput button_1(input_button_1_GPIO_Port, input_button_1_Pin);
DigitalInput button_2(input_button_2_GPIO_Port, input_button_2_Pin);
DigitalInput button_3(input_button_3_GPIO_Port, input_button_3_Pin);

DigitalOutput green_led(green_led_GPIO_Port, green_led_Pin);
DigitalOutput red_led(red_led_GPIO_Port, red_led_Pin);

I2CBus i2c2(&hi2c2);

DigitalOutput indicator{LedPin_GPIO_Port, LedPin_Pin};


UART_HandleTypeDef* debug_uart = &huart3;

}  // namespace mcal

namespace bindings {

shared::periph::DigitalInput& button_increment_pot0 = mcal::button_0;
shared::periph::DigitalInput& button_increment_pot1 = mcal::button_1;
shared::periph::DigitalInput& button_terminal_connection_pot0 = mcal::button_2;
shared::periph::DigitalInput& button_terminal_connection_pot1 = mcal::button_3;

shared::periph::DigitalOutput& red_led = mcal::red_led;
shared::periph::DigitalOutput& green_led = mcal::green_led;

shared::periph::I2CBus& i2c_bus1 = mcal::i2c2;



void Init() {
    SystemClock_Config();
    HAL_Init();
    MX_GPIO_Init();
    MX_I2C2_Init();
    MX_USART3_UART_Init();
    SetDebugUART(mcal::debug_uart);
}

void DelayMs(uint32_t ms) {
    HAL_Delay(ms);
}


}  // namespace bindings