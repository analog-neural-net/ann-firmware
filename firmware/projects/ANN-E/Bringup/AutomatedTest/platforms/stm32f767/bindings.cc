/// @author Hydar Zartash
/// @date 2025-03-02

#include <iostream>

// cubemx files
#include "adc.h"
#include "gpio.h"
#include "i2c.h"
#include "main.h"
#include "usart.h"


// fw includes
#include "../../bindings.hpp"
#include "mcal/stm32f767/periph/analog_input.hpp"
#include "mcal/stm32f767/periph/gpio.hpp"
#include "mcal/stm32f767/periph/i2c.hpp"
#include "mcal/stm32f767/periph/uart.hpp"
#include "mcal/stm32f767/util/stdio_retarget.h"
#include "shared/device/digital_pot.hpp"
#include "shared/device/i2c_mux.hpp"
#include "shared/device/mcp/mcp4461.hpp"
#include "shared/device/mcp/mcp4728.hpp"
#include "shared/device/ti/tca9548a.hpp"
#include "shared/periph/analog_input.hpp"
#include "shared/periph/analog_output.hpp"
#include "shared/periph/gpio.hpp"
#include "shared/periph/i2c.hpp"


// template metaporgramming include
#include <array>

extern "C" {
/**
 * This requires extern since it is not declared in a header, only defined
 * in cubemx/../main.c
 */
void SystemClock_Config();
}

constexpr uint8_t kMcp4461DefaultAddress = 0x2C;
constexpr uint8_t kNumPotsPerController = 4;

namespace mcal {
using namespace stm32f767::periph;

DigitalOutput red_led(red_led_GPIO_Port, red_led_Pin);
DigitalOutput green_led(green_led_GPIO_Port, green_led_Pin);
DigitalOutput heartbeat(UC_Heartbeat_GPIO_Port, UC_Heartbeat_Pin);

I2CBus i2c1(&hi2c1);
I2CBus i2c2(&hi2c2);
I2CBus i2c3(&hi2c3);

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

UART_HandleTypeDef* debug_uart = &huart3;
UartBus uart_bus{&huart3};

}  // namespace mcal

namespace device {
using namespace shared::device;

std::array<ti::TCA9548A, bindings::kNumi2cBuses> tca9548a_muxes = {
    ti::TCA9548A(mcal::i2c1, 0x70, true), ti::TCA9548A(mcal::i2c2, 0x70, true),
    ti::TCA9548A(mcal::i2c3, 0x70, true)};

std::array<std::array<I2CBusMultiplexed<ti::TCA9548AChannel>,
                      bindings::kNumi2cChannelsPerBus>,
           bindings::kNumi2cBuses>
    i2c_channels = {{{I2CBusMultiplexed<ti::TCA9548AChannel>{
                          tca9548a_muxes[0], ti::TCA9548AChannel::CHANNEL_A},
                      I2CBusMultiplexed<ti::TCA9548AChannel>{
                          tca9548a_muxes[0], ti::TCA9548AChannel::CHANNEL_B},
                      I2CBusMultiplexed<ti::TCA9548AChannel>{
                          tca9548a_muxes[0], ti::TCA9548AChannel::CHANNEL_C},
                      I2CBusMultiplexed<ti::TCA9548AChannel>{
                          tca9548a_muxes[0], ti::TCA9548AChannel::CHANNEL_D},
                      I2CBusMultiplexed<ti::TCA9548AChannel>{
                          tca9548a_muxes[0], ti::TCA9548AChannel::CHANNEL_E},
                      I2CBusMultiplexed<ti::TCA9548AChannel>{
                          tca9548a_muxes[0], ti::TCA9548AChannel::CHANNEL_F},
                      I2CBusMultiplexed<ti::TCA9548AChannel>{
                          tca9548a_muxes[0], ti::TCA9548AChannel::CHANNEL_G},
                      I2CBusMultiplexed<ti::TCA9548AChannel>{
                          tca9548a_muxes[0], ti::TCA9548AChannel::CHANNEL_H}},
                     {I2CBusMultiplexed<ti::TCA9548AChannel>{
                          tca9548a_muxes[1], ti::TCA9548AChannel::CHANNEL_A},
                      I2CBusMultiplexed<ti::TCA9548AChannel>{
                          tca9548a_muxes[1], ti::TCA9548AChannel::CHANNEL_B},
                      I2CBusMultiplexed<ti::TCA9548AChannel>{
                          tca9548a_muxes[1], ti::TCA9548AChannel::CHANNEL_C},
                      I2CBusMultiplexed<ti::TCA9548AChannel>{
                          tca9548a_muxes[1], ti::TCA9548AChannel::CHANNEL_D},
                      I2CBusMultiplexed<ti::TCA9548AChannel>{
                          tca9548a_muxes[1], ti::TCA9548AChannel::CHANNEL_E},
                      I2CBusMultiplexed<ti::TCA9548AChannel>{
                          tca9548a_muxes[1], ti::TCA9548AChannel::CHANNEL_F},
                      I2CBusMultiplexed<ti::TCA9548AChannel>{
                          tca9548a_muxes[1], ti::TCA9548AChannel::CHANNEL_G},
                      I2CBusMultiplexed<ti::TCA9548AChannel>{
                          tca9548a_muxes[1], ti::TCA9548AChannel::CHANNEL_H}},
                     {I2CBusMultiplexed<ti::TCA9548AChannel>{
                          tca9548a_muxes[2], ti::TCA9548AChannel::CHANNEL_A},
                      I2CBusMultiplexed<ti::TCA9548AChannel>{
                          tca9548a_muxes[2], ti::TCA9548AChannel::CHANNEL_B},
                      I2CBusMultiplexed<ti::TCA9548AChannel>{
                          tca9548a_muxes[2], ti::TCA9548AChannel::CHANNEL_C},
                      I2CBusMultiplexed<ti::TCA9548AChannel>{
                          tca9548a_muxes[2], ti::TCA9548AChannel::CHANNEL_D},
                      I2CBusMultiplexed<ti::TCA9548AChannel>{
                          tca9548a_muxes[2], ti::TCA9548AChannel::CHANNEL_E},
                      I2CBusMultiplexed<ti::TCA9548AChannel>{
                          tca9548a_muxes[2], ti::TCA9548AChannel::CHANNEL_F},
                      I2CBusMultiplexed<ti::TCA9548AChannel>{
                          tca9548a_muxes[2], ti::TCA9548AChannel::CHANNEL_G},
                      I2CBusMultiplexed<ti::TCA9548AChannel>{
                          tca9548a_muxes[2], ti::TCA9548AChannel::CHANNEL_H}}}};

std::array<std::array<std::array<mcp::MCP4461, bindings::kNumWeightsPerNeuron /
                                                   kNumPotsPerController>,
                      bindings::kNumNeuronsPerLayer>,
           bindings::kNumLayers>
    pot_controllers = {{{{{mcp::MCP4461(i2c_channels[0][0], 0x2C),
                           mcp::MCP4461(i2c_channels[0][1], 0x2C),
                           mcp::MCP4461(i2c_channels[0][2], 0x2C)},
                          {mcp::MCP4461(i2c_channels[0][0], 0x2D),
                           mcp::MCP4461(i2c_channels[0][1], 0x2D),
                           mcp::MCP4461(i2c_channels[0][2], 0x2D)},
                          {mcp::MCP4461(i2c_channels[0][0], 0x2E),
                           mcp::MCP4461(i2c_channels[0][1], 0x2E),
                           mcp::MCP4461(i2c_channels[0][2], 0x2E)},
                          {mcp::MCP4461(i2c_channels[0][0], 0x2F),
                           mcp::MCP4461(i2c_channels[0][1], 0x2F),
                           mcp::MCP4461(i2c_channels[0][2], 0x2F)},
                          {mcp::MCP4461(i2c_channels[1][0], 0x2C),
                           mcp::MCP4461(i2c_channels[1][1], 0x2C),
                           mcp::MCP4461(i2c_channels[1][2], 0x2C)},
                          {mcp::MCP4461(i2c_channels[1][0], 0x2D),
                           mcp::MCP4461(i2c_channels[1][1], 0x2D),
                           mcp::MCP4461(i2c_channels[1][2], 0x2D)},
                          {mcp::MCP4461(i2c_channels[1][0], 0x2E),
                           mcp::MCP4461(i2c_channels[1][1], 0x2E),
                           mcp::MCP4461(i2c_channels[1][2], 0x2E)},
                          {mcp::MCP4461(i2c_channels[1][0], 0x2F),
                           mcp::MCP4461(i2c_channels[1][1], 0x2F),
                           mcp::MCP4461(i2c_channels[1][2], 0x2F)},
                          {mcp::MCP4461(i2c_channels[2][0], 0x2C),
                           mcp::MCP4461(i2c_channels[2][1], 0x2C),
                           mcp::MCP4461(i2c_channels[2][2], 0x2C)},
                          {mcp::MCP4461(i2c_channels[2][0], 0x2D),
                           mcp::MCP4461(i2c_channels[2][1], 0x2D),
                           mcp::MCP4461(i2c_channels[2][2], 0x2D)},
                          {mcp::MCP4461(i2c_channels[2][0], 0x2E),
                           mcp::MCP4461(i2c_channels[2][1], 0x2E),
                           mcp::MCP4461(i2c_channels[2][2], 0x2E)},
                          {mcp::MCP4461(i2c_channels[2][0], 0x2F),
                           mcp::MCP4461(i2c_channels[2][1], 0x2F),
                           mcp::MCP4461(i2c_channels[2][2], 0x2F)}}},
                        {{{mcp::MCP4461(i2c_channels[0][4], 0x2C),
                           mcp::MCP4461(i2c_channels[0][5], 0x2C),
                           mcp::MCP4461(i2c_channels[0][6], 0x2C)},
                          {mcp::MCP4461(i2c_channels[0][4], 0x2D),
                           mcp::MCP4461(i2c_channels[0][5], 0x2D),
                           mcp::MCP4461(i2c_channels[0][6], 0x2D)},
                          {mcp::MCP4461(i2c_channels[0][4], 0x2E),
                           mcp::MCP4461(i2c_channels[0][5], 0x2E),
                           mcp::MCP4461(i2c_channels[0][6], 0x2E)},
                          {mcp::MCP4461(i2c_channels[0][4], 0x2F),
                           mcp::MCP4461(i2c_channels[0][5], 0x2F),
                           mcp::MCP4461(i2c_channels[0][6], 0x2F)},
                          {mcp::MCP4461(i2c_channels[1][4], 0x2C),
                           mcp::MCP4461(i2c_channels[1][5], 0x2C),
                           mcp::MCP4461(i2c_channels[1][6], 0x2C)},
                          {mcp::MCP4461(i2c_channels[1][4], 0x2D),
                           mcp::MCP4461(i2c_channels[1][5], 0x2D),
                           mcp::MCP4461(i2c_channels[1][6], 0x2D)},
                          {mcp::MCP4461(i2c_channels[1][4], 0x2E),
                           mcp::MCP4461(i2c_channels[1][5], 0x2E),
                           mcp::MCP4461(i2c_channels[1][6], 0x2E)},
                          {mcp::MCP4461(i2c_channels[1][4], 0x2F),
                           mcp::MCP4461(i2c_channels[1][5], 0x2F),
                           mcp::MCP4461(i2c_channels[1][6], 0x2F)},
                          {mcp::MCP4461(i2c_channels[2][4], 0x2C),
                           mcp::MCP4461(i2c_channels[2][5], 0x2C),
                           mcp::MCP4461(i2c_channels[2][6], 0x2C)},
                          {mcp::MCP4461(i2c_channels[2][4], 0x2D),
                           mcp::MCP4461(i2c_channels[2][5], 0x2D),
                           mcp::MCP4461(i2c_channels[2][6], 0x2D)}}}}};

std::array<std::array<mcp::MCP4461,
                      bindings::kNumNeuronsPerLayer / kNumPotsPerController>,
           bindings::kNumLayers>
    bias_controllers = {{{
                             mcp::MCP4461(i2c_channels[0][3], 0x2C),
                             mcp::MCP4461(i2c_channels[1][3], 0x2C),
                             mcp::MCP4461(i2c_channels[2][3], 0x2C),
                         },
                         {
                             mcp::MCP4461(i2c_channels[0][7], 0x2C),
                             mcp::MCP4461(i2c_channels[1][7], 0x2C),
                             mcp::MCP4461(i2c_channels[2][7], 0x2C),
                         }}};

std::array<std::array<mcp::MCP4461,
                      bindings::kNumNeuronsPerLayer / kNumPotsPerController>,
           bindings::kNumLayers>
    feedback_controllers = {{{
                                 mcp::MCP4461(i2c_channels[0][3], 0x2D),
                                 mcp::MCP4461(i2c_channels[1][3], 0x2D),
                                 mcp::MCP4461(i2c_channels[2][3], 0x2D),
                             },
                             {
                                 mcp::MCP4461(i2c_channels[0][7], 0x2D),
                                 mcp::MCP4461(i2c_channels[1][7], 0x2D),
                                 mcp::MCP4461(i2c_channels[2][7], 0x2D),
                             }}};

// // single wn block

mcp::MCP4728 dac0(i2c_channels[0][0], 0x60, 2.75F, -2.75F);
mcp::MCP4728 dac1(i2c_channels[1][0], 0x60, 2.75F, -2.75F);
mcp::MCP4728 dac2(i2c_channels[2][0], 0x60, 2.75F, -2.75F);

// immediately invoed lambda to initialize the weight pots
auto weight_pots = []() {
    std::array<std::array<std::array<DigitalPotentiometer<uint8_t>,
                                     bindings::kNumWeightsPerNeuron>,
                          bindings::kNumNeuronsPerLayer>,
               bindings::kNumLayers>
        weight_pots_array = {};
    for (uint8_t layer = 0; layer < bindings::kNumLayers; layer++) {
        for (uint8_t neuron = 0; neuron < bindings::kNumNeuronsPerLayer;
             neuron++) {
            for (uint8_t weight = 0; weight < bindings::kNumWeightsPerNeuron;
                 weight++) {
                weight_pots_array[layer][neuron][weight] =
                    DigitalPotentiometer<uint8_t>(
                        pot_controllers[layer][neuron]
                                       [weight / kNumPotsPerController],
                        weight % kNumPotsPerController);
            }
        }
    }
    return weight_pots_array;
}();

auto bias_pots = []() {
    std::array<std::array<DigitalPotentiometer<uint8_t>,
                          bindings::kNumNeuronsPerLayer>,
               bindings::kNumLayers>
        bias_pot_array = {};
    for (uint8_t layer = 0; layer < bindings::kNumLayers; layer++) {
        for (uint8_t neuron = 0; neuron < bindings::kNumNeuronsPerLayer;
             neuron++) {
            bias_pot_array[layer][neuron] = DigitalPotentiometer<uint8_t>(
                bias_controllers[layer][neuron / kNumPotsPerController],
                neuron % kNumPotsPerController);
        }
    }
    return bias_pot_array;
}();

auto feedback_pots = []() {
    std::array<std::array<DigitalPotentiometer<uint8_t>,
                          bindings::kNumNeuronsPerLayer>,
               bindings::kNumLayers>
        feedback_pot_array = {};
    for (uint8_t layer = 0; layer < bindings::kNumLayers; layer++) {
        for (uint8_t neuron = 0; neuron < bindings::kNumNeuronsPerLayer;
             neuron++) {
            feedback_pot_array[layer][neuron] = DigitalPotentiometer<uint8_t>(
                feedback_controllers[layer][neuron / kNumPotsPerController],
                neuron % kNumPotsPerController);
        }
    }
    return feedback_pot_array;
}();

}  // namespace device

namespace bindings {
shared::periph::DigitalOutput& red_led = mcal::red_led;
shared::periph::DigitalOutput& green_led = mcal::green_led;
shared::periph::DigitalOutput& heartbeat = mcal::heartbeat;

shared::periph::I2CBus& i2c1 = mcal::i2c1;
shared::periph::I2CBus& i2c2 = mcal::i2c2;
shared::periph::I2CBus& i2c3 = mcal::i2c3;
shared::periph::UartBus& uart_bus = mcal::uart_bus;

std::array<std::array<std::array<shared::device::DigitalPotentiometer<uint8_t>,
                                 kNumWeightsPerNeuron>,
                      bindings::kNumNeuronsPerLayer>,
           bindings::kNumLayers>
    pots = device::weight_pots;

shared::periph::AnalogOutputGroup<kNumAnalogOutputs>& analog_output_group_0 =
    device::dac0;
shared::periph::AnalogOutputGroup<kNumAnalogOutputs>& analog_output_group_1 =
    device::dac1;
shared::periph::AnalogOutputGroup<kNumAnalogOutputs>& analog_output_group_2 =
    device::dac2;

shared::periph::AnalogInput& analog_input_1 = mcal::analog_input_1;
shared::periph::AnalogInput& analog_input_2 = mcal::analog_input_2;
shared::periph::AnalogInput& analog_input_0 = mcal::analog_input_0;
shared::periph::AnalogInput& analog_input_3 = mcal::analog_input_3;
shared::periph::AnalogInput& analog_input_4 = mcal::analog_input_4;
shared::periph::AnalogInput& analog_input_5 = mcal::analog_input_5;
shared::periph::AnalogInput& analog_input_6 = mcal::analog_input_6;
shared::periph::AnalogInput& analog_input_7 = mcal::analog_input_7;
shared::periph::AnalogInput& analog_input_8 = mcal::analog_input_8;
shared::periph::AnalogInput& analog_input_9 = mcal::analog_input_9;

std::array<shared::periph::AnalogInput*, kOutputLayerSize> adc_channels = {
    &analog_input_0, &analog_input_1, &analog_input_2, &analog_input_3,
    &analog_input_4, &analog_input_5, &analog_input_6, &analog_input_7,
    &analog_input_8, &analog_input_9};


std::array<std::array<shared::device::DigitalPotentiometer<uint8_t>,
                      bindings::kNumNeuronsPerLayer>,
           bindings::kNumLayers>
    bias_pots = device::bias_pots;
std::array<std::array<shared::device::DigitalPotentiometer<uint8_t>,
                      bindings::kNumNeuronsPerLayer>,
           bindings::kNumLayers>
    fb_pots = device::feedback_pots;

void Init() {
    SystemClock_Config();
    HAL_Init();
    MX_GPIO_Init();
    MX_USART3_UART_Init();

    MX_ADC3_Init();

    MX_I2C1_Init();
    MX_I2C2_Init();
    MX_I2C3_Init();

    SetDebugUART(mcal::debug_uart);
    device::dac0.SetChannelVoltageReference();
    device::dac1.SetChannelVoltageReference();
    device::dac2.SetChannelVoltageReference();

    std::cout << "Begin" << std::endl;
}

uint32_t GetTimeMs() {
    return HAL_GetTick();
}

void DelayMs(uint32_t ms) {
    HAL_Delay(ms);
}

}  // namespace bindings
