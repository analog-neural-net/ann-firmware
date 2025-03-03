/// @author Hydar Zartash
/// @date 2025-03-02

#include <iostream>

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
#include "shared/device/ti/tca9548a.hpp"
#include "shared/device/i2c_mux.hpp"
#include "shared/periph/analog_output.hpp"
#include "shared/periph/i2c.hpp"

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
DigitalOutput green_led(green_led_GPIO_Port, green_led_Pin);
DigitalOutput heartbeat(UC_Heartbeat_GPIO_Port, UC_Heartbeat_Pin);

I2CBus i2c1(&hi2c1);
I2CBus i2c2(&hi2c2);
I2CBus i2c3(&hi2c3);

UART_HandleTypeDef* debug_uart = &huart3;
}  // namespace mcal

namespace device {
using namespace shared::device;

ti::TCA9548A tca9548a(mcal::i2c3, 0x70, true);
I2CBusMultiplexed<ti::TCA9548AChannel> i2c1A{
    tca9548a, ti::TCA9548AChannel::CHANNEL_A};

mcp::MCP4728 dac(bindings::i2c1A, 0x60, 5.F, 0.F);
}  // namespace device


namespace bindings {
shared::periph::DigitalOutput& red_led = mcal::red_led;
shared::periph::DigitalOutput& green_led = mcal::green_led;
shared::periph::DigitalOutput& heartbeat = mcal::heartbeat;

shared::periph::I2CBus& i2c1 = mcal::i2c1;
shared::periph::I2CBus& i2c2 = mcal::i2c2;
shared::periph::I2CBus& i2c3 = mcal::i2c3;

shared::periph::I2CBus& i2c1A = device::i2c1A;
shared::periph::AnalogOutputGroup<kNumAnalogOutputs>& analog_output_group = device::dac;

void Init() {
    SystemClock_Config();
    HAL_Init();
    MX_GPIO_Init();
    MX_USART3_UART_Init();
    
    MX_I2C1_Init();
    MX_I2C2_Init();
    MX_I2C3_Init();

    SetDebugUART(mcal::debug_uart);
    device::dac.SetChannelVoltageReference();

    std::cout << "Hello World!" << std::endl;
}

void DelayMs(uint32_t ms)
{
    HAL_Delay(ms);
}

}  // namespace bindings
