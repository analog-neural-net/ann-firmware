/// @author Hydar Zartash
/// @date 2025-03-02

#include <iostream>

// cubemx files
#include "gpio.h"
#include "adc.h"
#include "usart.h"
#include "main.h"

// fw includes
#include "../../bindings.hpp"
#include "mcal/stm32f767/periph/gpio.hpp"
#include "mcal/stm32f767/util/stdio_retarget.h"
#include "mcal/stm32f767/periph/analog_input.hpp"
#include "shared/periph/gpio.hpp"
#include "shared/periph/analog_input.hpp"
#include "shared/device/current_sensor.hpp"
#include "shared/device/ace/mca110153.hpp"

extern "C" {
/**
 * This requires extern since it is not declared in a header, only defined
 * in cubemx/../main.c
 */
void SystemClock_Config();
}

namespace mcal {
using namespace stm32f767::periph;

AnalogInput analog_input_0{&hadc3, ADC_CHANNEL_0};
AnalogInput analog_input_1{&hadc3, ADC_CHANNEL_1};
AnalogInput analog_input_2{&hadc3, ADC_CHANNEL_2};
AnalogInput analog_input_3{&hadc3, ADC_CHANNEL_3};
AnalogInput analog_input_4{&hadc3, ADC_CHANNEL_4};
AnalogInput analog_input_5{&hadc3, ADC_CHANNEL_5};
AnalogInput analog_input_6{&hadc3, ADC_CHANNEL_6};
AnalogInput analog_input_7{&hadc3, ADC_CHANNEL_7};
AnalogInput analog_input_8{&hadc3, ADC_CHANNEL_8};
AnalogInput analog_input_9{&hadc3, ADC_CHANNEL_9};

AnalogInput current_sensor_read{&hadc2, ADC_CHANNEL_6};
AnalogInput current_sensor_ref{&hadc2, ADC_CHANNEL_7};



DigitalOutput red_led(red_led_GPIO_Port, red_led_Pin);
DigitalOutput green_led(green_led_GPIO_Port, green_led_Pin);
DigitalOutput heartbeat(UC_Heartbeat_GPIO_Port, UC_Heartbeat_Pin);

UART_HandleTypeDef* debug_uart = &huart3;
}  // namespace mcal

namespace device {
using namespace shared::device;
    ace::MCA1101_5_3 current_sensor(mcal::current_sensor_ref, mcal::current_sensor_read);
}


namespace bindings {
shared::periph::DigitalOutput& red_led = mcal::red_led;
shared::periph::DigitalOutput& green_led = mcal::green_led;
shared::periph::DigitalOutput& heartbeat = mcal::heartbeat;

shared::periph::AnalogInput& analog_input_0 = mcal::analog_input_0;
shared::periph::AnalogInput& analog_input_1 = mcal::analog_input_1;
shared::periph::AnalogInput& analog_input_2 = mcal::analog_input_2;
shared::periph::AnalogInput& analog_input_3 = mcal::analog_input_3;
shared::periph::AnalogInput& analog_input_4 = mcal::analog_input_4;
shared::periph::AnalogInput& analog_input_5 = mcal::analog_input_5;
shared::periph::AnalogInput& analog_input_6 = mcal::analog_input_6;
shared::periph::AnalogInput& analog_input_7 = mcal::analog_input_7;
shared::periph::AnalogInput& analog_input_8 = mcal::analog_input_8;
shared::periph::AnalogInput& analog_input_9 = mcal::analog_input_9;

shared::periph::AnalogInput& current_sensor_read = mcal::current_sensor_read;
shared::periph::AnalogInput& current_sensor_ref = mcal::current_sensor_ref;

shared::device::CurrentSensor& current_sensor = device::current_sensor;



void Init() {
    SystemClock_Config();
    HAL_Init();
    MX_GPIO_Init();
    MX_USART3_UART_Init();

    MX_ADC2_Init();
    MX_ADC3_Init();
    
    SetDebugUART(mcal::debug_uart);

    std::cout << "Hello World!" << std::endl;
}

void DelayMs(uint32_t ms)
{
    HAL_Delay(ms);
}

}  // namespace bindings
