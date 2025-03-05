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
#include <vector>

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

    constexpr uint8_t kNumi2cBuses = 3;
    constexpr uint8_t kNumi2cChannelsPerBus = 8;
    constexpr uint8_t kNumWeightsPerNeuron

    constexpr std::array<ti::TCA9548A, kNumi2cBuses> tca9548a_muxes = {
        ti::TCA9548A(mcal::i2c1, 0x70, true),
        ti::TCA9548A(mcal::i2c2, 0x70, true),
        ti::TCA9548A(mcal::i2c3, 0x70, true)
    };

    constexpr std::array<std::array<I2CBusMultiplexed<ti::TCA9548AChannel>, kNumi2cChannelsPerBus>, kNumi2cBuses> i2c_channels = {{
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



    I2CBusMultiplexed<ti::TCA9548AChannel> i2c1A{tca9548a_muxes[0], ti::TCA9548AChannel::CHANNEL_A};
    I2CBusMultiplexed<ti::TCA9548AChannel> i2c1B{tca9548a_muxes[0], ti::TCA9548AChannel::CHANNEL_B};
    I2CBusMultiplexed<ti::TCA9548AChannel> i2c1C{tca9548a_muxes[0], ti::TCA9548AChannel::CHANNEL_C};
    I2CBusMultiplexed<ti::TCA9548AChannel> i2c1D{tca9548a_muxes[0], ti::TCA9548AChannel::CHANNEL_D};
    I2CBusMultiplexed<ti::TCA9548AChannel> i2c1E{tca9548a_muxes[0], ti::TCA9548AChannel::CHANNEL_E};
    I2CBusMultiplexed<ti::TCA9548AChannel> i2c1F{tca9548a_muxes[0], ti::TCA9548AChannel::CHANNEL_F};
    I2CBusMultiplexed<ti::TCA9548AChannel> i2c1G{tca9548a_muxes[0], ti::TCA9548AChannel::CHANNEL_G};    
    I2CBusMultiplexed<ti::TCA9548AChannel> i2c1H{tca9548a_muxes[0], ti::TCA9548AChannel::CHANNEL_H};    
    I2CBusMultiplexed<ti::TCA9548AChannel> i2c2A{tca9548a_muxes[1], ti::TCA9548AChannel::CHANNEL_A};
    I2CBusMultiplexed<ti::TCA9548AChannel> i2c2B{tca9548a_muxes[1], ti::TCA9548AChannel::CHANNEL_B};
    I2CBusMultiplexed<ti::TCA9548AChannel> i2c2C{tca9548a_muxes[1], ti::TCA9548AChannel::CHANNEL_C};
    I2CBusMultiplexed<ti::TCA9548AChannel> i2c2D{tca9548a_muxes[1], ti::TCA9548AChannel::CHANNEL_D};
    I2CBusMultiplexed<ti::TCA9548AChannel> i2c2E{tca9548a_muxes[1], ti::TCA9548AChannel::CHANNEL_E};
    I2CBusMultiplexed<ti::TCA9548AChannel> i2c2F{tca9548a_muxes[1], ti::TCA9548AChannel::CHANNEL_F};
    I2CBusMultiplexed<ti::TCA9548AChannel> i2c2G{tca9548a_muxes[1], ti::TCA9548AChannel::CHANNEL_G};    
    I2CBusMultiplexed<ti::TCA9548AChannel> i2c2H{tca9548a_muxes[1], ti::TCA9548AChannel::CHANNEL_H};    
    I2CBusMultiplexed<ti::TCA9548AChannel> i2c3A{tca9548a_muxes[2], ti::TCA9548AChannel::CHANNEL_A};
    I2CBusMultiplexed<ti::TCA9548AChannel> i2c3B{tca9548a_muxes[2], ti::TCA9548AChannel::CHANNEL_B};
    I2CBusMultiplexed<ti::TCA9548AChannel> i2c3C{tca9548a_muxes[2], ti::TCA9548AChannel::CHANNEL_C};
    I2CBusMultiplexed<ti::TCA9548AChannel> i2c3D{tca9548a_muxes[2], ti::TCA9548AChannel::CHANNEL_D};
    I2CBusMultiplexed<ti::TCA9548AChannel> i2c3E{tca9548a_muxes[2], ti::TCA9548AChannel::CHANNEL_E};
    I2CBusMultiplexed<ti::TCA9548AChannel> i2c3F{tca9548a_muxes[2], ti::TCA9548AChannel::CHANNEL_F};
    I2CBusMultiplexed<ti::TCA9548AChannel> i2c3G{tca9548a_muxes[2], ti::TCA9548AChannel::CHANNEL_G};    
    I2CBusMultiplexed<ti::TCA9548AChannel> i2c3H{tca9548a_muxes[2], ti::TCA9548AChannel::CHANNEL_H};
    

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
    mcp::MCP4461 pot_control_l0n03f(bindings::i2c1D, 0x2C);
    mcp::MCP4461 pot_control_l0n03b(bindings::i2c1D, 0x2D);


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

shared::periph::I2CBus& i2c1A = device::i2c1A;
shared::periph::I2CBus& i2c1B = device::i2c1B;
shared::periph::I2CBus& i2c1C = device::i2c1C;
shared::periph::I2CBus& i2c1D = device::i2c1D;
shared::periph::I2CBus& i2c1E = device::i2c1E;
shared::periph::I2CBus& i2c1F = device::i2c1F;
shared::periph::I2CBus& i2c1G = device::i2c1G;
shared::periph::I2CBus& i2c1H = device::i2c1H;
shared::periph::I2CBus& i2c2A = device::i2c2A;
shared::periph::I2CBus& i2c2B = device::i2c2B;
shared::periph::I2CBus& i2c2C = device::i2c2C;
shared::periph::I2CBus& i2c2D = device::i2c2D;
shared::periph::I2CBus& i2c2E = device::i2c2E;
shared::periph::I2CBus& i2c2F = device::i2c2F;
shared::periph::I2CBus& i2c2G = device::i2c2G;
shared::periph::I2CBus& i2c2H = device::i2c2H;
shared::periph::I2CBus& i2c3A = device::i2c3A;
shared::periph::I2CBus& i2c3B = device::i2c3B;
shared::periph::I2CBus& i2c3C = device::i2c3C;
shared::periph::I2CBus& i2c3D = device::i2c3D;
shared::periph::I2CBus& i2c3E = device::i2c3E;
shared::periph::I2CBus& i2c3F = device::i2c3F;
shared::periph::I2CBus& i2c3G = device::i2c3G;
shared::periph::I2CBus& i2c3H = device::i2c3H;




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
