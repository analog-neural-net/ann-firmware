/// @author Hydar Zartash
/// @date 2025-03-02

#include <sys/_stdint.h>
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
#include "shared/device/mcp/mcp4461.hpp"
#include "shared/device/ti/tca9548a.hpp"
#include "shared/device/i2c_mux.hpp"
#include "shared/periph/analog_output.hpp"
#include "shared/device/digital_pot.hpp"
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




    // constexpr std::array<ti::TCA9548A, kNumi2cBuses> tca9548a_muxes = {
    //     ti::TCA9548A(mcal::i2c1, 0x70, true),
    //     ti::TCA9548A(mcal::i2c2, 0x70, true),
    //     ti::TCA9548A(mcal::i2c3, 0x70, true)
    // };

    //save the template programming for later
    std::array<ti::TCA9548A, bindings::kNumi2cBuses> tca9548a_muxes = {
        ti::TCA9548A(mcal::i2c1, 0x70, true),
        ti::TCA9548A(mcal::i2c2, 0x70, true),
        ti::TCA9548A(mcal::i2c3, 0x70, true)
    };

    std::array<std::array<I2CBusMultiplexed<ti::TCA9548AChannel>, bindings::kNumi2cChannelsPerBus>, bindings::kNumi2cBuses> i2c_channels = {{
        {
            I2CBusMultiplexed<ti::TCA9548AChannel>{tca9548a_muxes[0], ti::TCA9548AChannel::CHANNEL_A},
            I2CBusMultiplexed<ti::TCA9548AChannel>{tca9548a_muxes[0], ti::TCA9548AChannel::CHANNEL_B},
            I2CBusMultiplexed<ti::TCA9548AChannel>{tca9548a_muxes[0], ti::TCA9548AChannel::CHANNEL_C},
            I2CBusMultiplexed<ti::TCA9548AChannel>{tca9548a_muxes[0], ti::TCA9548AChannel::CHANNEL_D},
            I2CBusMultiplexed<ti::TCA9548AChannel>{tca9548a_muxes[0], ti::TCA9548AChannel::CHANNEL_E},
            I2CBusMultiplexed<ti::TCA9548AChannel>{tca9548a_muxes[0], ti::TCA9548AChannel::CHANNEL_F},
            I2CBusMultiplexed<ti::TCA9548AChannel>{tca9548a_muxes[0], ti::TCA9548AChannel::CHANNEL_G},
            I2CBusMultiplexed<ti::TCA9548AChannel>{tca9548a_muxes[0], ti::TCA9548AChannel::CHANNEL_H}
        },
        {
            I2CBusMultiplexed<ti::TCA9548AChannel>{tca9548a_muxes[1], ti::TCA9548AChannel::CHANNEL_A},
            I2CBusMultiplexed<ti::TCA9548AChannel>{tca9548a_muxes[1], ti::TCA9548AChannel::CHANNEL_B},
            I2CBusMultiplexed<ti::TCA9548AChannel>{tca9548a_muxes[1], ti::TCA9548AChannel::CHANNEL_C},
            I2CBusMultiplexed<ti::TCA9548AChannel>{tca9548a_muxes[1], ti::TCA9548AChannel::CHANNEL_D},
            I2CBusMultiplexed<ti::TCA9548AChannel>{tca9548a_muxes[1], ti::TCA9548AChannel::CHANNEL_E},
            I2CBusMultiplexed<ti::TCA9548AChannel>{tca9548a_muxes[1], ti::TCA9548AChannel::CHANNEL_F},
            I2CBusMultiplexed<ti::TCA9548AChannel>{tca9548a_muxes[1], ti::TCA9548AChannel::CHANNEL_G},
            I2CBusMultiplexed<ti::TCA9548AChannel>{tca9548a_muxes[1], ti::TCA9548AChannel::CHANNEL_H}
        },
        {
            I2CBusMultiplexed<ti::TCA9548AChannel>{tca9548a_muxes[2], ti::TCA9548AChannel::CHANNEL_A},
            I2CBusMultiplexed<ti::TCA9548AChannel>{tca9548a_muxes[2], ti::TCA9548AChannel::CHANNEL_B},
            I2CBusMultiplexed<ti::TCA9548AChannel>{tca9548a_muxes[2], ti::TCA9548AChannel::CHANNEL_C},
            I2CBusMultiplexed<ti::TCA9548AChannel>{tca9548a_muxes[2], ti::TCA9548AChannel::CHANNEL_D},
            I2CBusMultiplexed<ti::TCA9548AChannel>{tca9548a_muxes[2], ti::TCA9548AChannel::CHANNEL_E},
            I2CBusMultiplexed<ti::TCA9548AChannel>{tca9548a_muxes[2], ti::TCA9548AChannel::CHANNEL_F},
            I2CBusMultiplexed<ti::TCA9548AChannel>{tca9548a_muxes[2], ti::TCA9548AChannel::CHANNEL_G},
            I2CBusMultiplexed<ti::TCA9548AChannel>{tca9548a_muxes[2], ti::TCA9548AChannel::CHANNEL_H}
        }
    }};
    

    // // single wn block
    //neuron 0
    mcp::MCP4461 pot_control_l0n0c0(bindings::i2c1A, 0x2C);
    mcp::MCP4461 pot_control_l0n0c1(bindings::i2c1B, 0x2C);
    mcp::MCP4461 pot_control_l0n0c2(bindings::i2c1C, 0x2C);
    //neuron 1
    mcp::MCP4461 pot_control_l0n1c0(bindings::i2c1A, 0x2D);
    mcp::MCP4461 pot_control_l0n1c1(bindings::i2c1B, 0x2D);
    mcp::MCP4461 pot_control_l0n1c2(bindings::i2c1C, 0x2D); 
    //neuron 2
    mcp::MCP4461 pot_control_l0n2c0(bindings::i2c1A, 0x2E);
    mcp::MCP4461 pot_control_l0n2c1(bindings::i2c1B, 0x2E);
    mcp::MCP4461 pot_control_l0n2c2(bindings::i2c1C, 0x2E);
    // neuron 3
    mcp::MCP4461 pot_control_l0n3c0(bindings::i2c1A, 0x2F);
    mcp::MCP4461 pot_control_l0n3c1(bindings::i2c1B, 0x2F);
    mcp::MCP4461 pot_control_l0n3c2(bindings::i2c1C, 0x2F);
    
    //bias
    mcp::MCP4461 pot_control_l0n03f(bindings::i2c1D, 0x2D);
    mcp::MCP4461 pot_control_l0n03b(bindings::i2c1D, 0x2C);




    // // single wn block

    mcp::MCP4728 dac(bindings::i2c1A, 0x60, 5.5F, 0.F);

    DigitalPotentiometer<uint8_t> pot_l0n0w0(pot_control_l0n0c0, 0);
    DigitalPotentiometer<uint8_t> pot_l0n0w1(pot_control_l0n0c0, 1);
    DigitalPotentiometer<uint8_t> pot_l0n0w2(pot_control_l0n0c0, 2);
    DigitalPotentiometer<uint8_t> pot_l0n0w3(pot_control_l0n0c0, 3); 
    DigitalPotentiometer<uint8_t> pot_l0n0w4(pot_control_l0n0c1, 0);
    DigitalPotentiometer<uint8_t> pot_l0n0w5(pot_control_l0n0c1, 1);
    DigitalPotentiometer<uint8_t> pot_l0n0w6(pot_control_l0n0c1, 2);
    DigitalPotentiometer<uint8_t> pot_l0n0w7(pot_control_l0n0c1, 3);
    DigitalPotentiometer<uint8_t> pot_l0n0w8(pot_control_l0n0c2, 0);
    DigitalPotentiometer<uint8_t> pot_l0n0w9(pot_control_l0n0c2, 1);
    DigitalPotentiometer<uint8_t> pot_l0n0w10(pot_control_l0n0c2, 2);
    DigitalPotentiometer<uint8_t> pot_l0n0w11(pot_control_l0n0c2, 3);

    DigitalPotentiometer<uint8_t> pot_l0n1w0(pot_control_l0n1c0, 0);
    DigitalPotentiometer<uint8_t> pot_l0n1w1(pot_control_l0n1c0, 1);
    DigitalPotentiometer<uint8_t> pot_l0n1w2(pot_control_l0n1c0, 2);
    DigitalPotentiometer<uint8_t> pot_l0n1w3(pot_control_l0n1c0, 3); 
    DigitalPotentiometer<uint8_t> pot_l0n1w4(pot_control_l0n1c1, 0);
    DigitalPotentiometer<uint8_t> pot_l0n1w5(pot_control_l0n1c1, 1);
    DigitalPotentiometer<uint8_t> pot_l0n1w6(pot_control_l0n1c1, 2);
    DigitalPotentiometer<uint8_t> pot_l0n1w7(pot_control_l0n1c1, 3);
    DigitalPotentiometer<uint8_t> pot_l0n1w8(pot_control_l0n1c2, 0);
    DigitalPotentiometer<uint8_t> pot_l0n1w9(pot_control_l0n1c2, 1);
    DigitalPotentiometer<uint8_t> pot_l0n1w10(pot_control_l0n1c2, 2);
    DigitalPotentiometer<uint8_t> pot_l0n1w11(pot_control_l0n1c2, 3);

    DigitalPotentiometer<uint8_t> pot_l0n2w0(pot_control_l0n2c0, 0);
    DigitalPotentiometer<uint8_t> pot_l0n2w1(pot_control_l0n2c0, 1);
    DigitalPotentiometer<uint8_t> pot_l0n2w2(pot_control_l0n2c0, 2);
    DigitalPotentiometer<uint8_t> pot_l0n2w3(pot_control_l0n2c0, 3); 
    DigitalPotentiometer<uint8_t> pot_l0n2w4(pot_control_l0n2c1, 0);
    DigitalPotentiometer<uint8_t> pot_l0n2w5(pot_control_l0n2c1, 1);
    DigitalPotentiometer<uint8_t> pot_l0n2w6(pot_control_l0n2c1, 2);
    DigitalPotentiometer<uint8_t> pot_l0n2w7(pot_control_l0n2c1, 3);
    DigitalPotentiometer<uint8_t> pot_l0n2w8(pot_control_l0n2c2, 0);
    DigitalPotentiometer<uint8_t> pot_l0n2w9(pot_control_l0n2c2, 1);
    DigitalPotentiometer<uint8_t> pot_l0n2w10(pot_control_l0n2c2, 2);
    DigitalPotentiometer<uint8_t> pot_l0n2w11(pot_control_l0n2c2, 3);
    
    DigitalPotentiometer<uint8_t> pot_l0n3w0(pot_control_l0n3c0, 0);
    DigitalPotentiometer<uint8_t> pot_l0n3w1(pot_control_l0n3c0, 1);
    DigitalPotentiometer<uint8_t> pot_l0n3w2(pot_control_l0n3c0, 2);
    DigitalPotentiometer<uint8_t> pot_l0n3w3(pot_control_l0n3c0, 3); 
    DigitalPotentiometer<uint8_t> pot_l0n3w4(pot_control_l0n3c1, 0);
    DigitalPotentiometer<uint8_t> pot_l0n3w5(pot_control_l0n3c1, 1);
    DigitalPotentiometer<uint8_t> pot_l0n3w6(pot_control_l0n3c1, 2);
    DigitalPotentiometer<uint8_t> pot_l0n3w7(pot_control_l0n3c1, 3);
    DigitalPotentiometer<uint8_t> pot_l0n3w8(pot_control_l0n3c2, 0);
    DigitalPotentiometer<uint8_t> pot_l0n3w9(pot_control_l0n3c2, 1);
    DigitalPotentiometer<uint8_t> pot_l0n3w10(pot_control_l0n3c2, 2);
    DigitalPotentiometer<uint8_t> pot_l0n3w11(pot_control_l0n3c2, 3);


    DigitalPotentiometer<uint8_t> pot_l0n0b(pot_control_l0n03b, 0);
    DigitalPotentiometer<uint8_t> pot_l0n1b(pot_control_l0n03b, 1);
    DigitalPotentiometer<uint8_t> pot_l0n2b(pot_control_l0n03b, 2);
    DigitalPotentiometer<uint8_t> pot_l0n3b(pot_control_l0n03b, 3); 
    
    DigitalPotentiometer<uint8_t> pot_l0n0f(pot_control_l0n03f, 0);
    DigitalPotentiometer<uint8_t> pot_l0n1f(pot_control_l0n03f, 1);
    DigitalPotentiometer<uint8_t> pot_l0n2f(pot_control_l0n03f, 2);
    DigitalPotentiometer<uint8_t> pot_l0n3f(pot_control_l0n03f, 3);


}  // namespace device


namespace bindings {
shared::periph::DigitalOutput& red_led = mcal::red_led;
shared::periph::DigitalOutput& green_led = mcal::green_led;
shared::periph::DigitalOutput& heartbeat = mcal::heartbeat;

shared::periph::I2CBus& i2c1 = mcal::i2c1;
shared::periph::I2CBus& i2c2 = mcal::i2c2;
shared::periph::I2CBus& i2c3 = mcal::i2c3;



shared::periph::I2CBus& i2c1A = device::i2c_channels[2][0+4];
shared::periph::I2CBus& i2c1B = device::i2c_channels[2][1+4];
shared::periph::I2CBus& i2c1C = device::i2c_channels[2][2+4];
shared::periph::I2CBus& i2c1D = device::i2c_channels[2][3+4];

std::array<std::array<shared::device::DigitalPotentiometer<uint8_t>, kNumWeightsPerNeuron>, kNumNeuronsPerLayer> pots = {
    {{
        device::pot_l0n0w0,
        device::pot_l0n0w1,
        device::pot_l0n0w2,
        device::pot_l0n0w3,
        device::pot_l0n0w4,
        device::pot_l0n0w5,
        device::pot_l0n0w6,
        device::pot_l0n0w7,
        device::pot_l0n0w8,
        device::pot_l0n0w9,
        device::pot_l0n0w10,
        device::pot_l0n0w11
    },
    {
        device::pot_l0n1w0,
        device::pot_l0n1w1,
        device::pot_l0n1w2,
        device::pot_l0n1w3,
        device::pot_l0n1w4,
        device::pot_l0n1w5,
        device::pot_l0n1w6,
        device::pot_l0n1w7,
        device::pot_l0n1w8,
        device::pot_l0n1w9,
        device::pot_l0n1w10,
        device::pot_l0n1w11
    },
    {
        device::pot_l0n2w0,
        device::pot_l0n2w1,
        device::pot_l0n2w2,
        device::pot_l0n2w3,
        device::pot_l0n2w4,
        device::pot_l0n2w5,
        device::pot_l0n2w6,
        device::pot_l0n2w7,
        device::pot_l0n2w8,
        device::pot_l0n2w9,
        device::pot_l0n2w10,
        device::pot_l0n2w11
    },
    {
        device::pot_l0n3w0,
        device::pot_l0n3w1,
        device::pot_l0n3w2,
        device::pot_l0n3w3,
        device::pot_l0n3w4,
        device::pot_l0n3w5,
        device::pot_l0n3w6,
        device::pot_l0n3w7,
        device::pot_l0n3w8,
        device::pot_l0n3w9,
        device::pot_l0n3w10,
        device::pot_l0n3w11
    }
}};

std::array<shared::device::DigitalPotentiometer<uint8_t>, kNumNeuronsPerLayer> bias_pots = {
    device::pot_l0n0b,
    device::pot_l0n1b,
    device::pot_l0n2b,
    device::pot_l0n3b
};

std::array<shared::device::DigitalPotentiometer<uint8_t>, kNumNeuronsPerLayer> fb_pots = {
    device::pot_l0n0f,
    device::pot_l0n1f,
    device::pot_l0n2f,
    device::pot_l0n3f
};

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
    // device::dac.SetChannelVoltageReference();
    std::cout << "Begin" << std::endl;

}

void DelayMs(uint32_t ms)
{
    HAL_Delay(ms);
}

}  // namespace bindings
