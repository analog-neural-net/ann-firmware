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
    //neuron 4
    mcp::MCP4461 pot_control_l0n4c0(bindings::i2c2A, 0x2C);
    mcp::MCP4461 pot_control_l0n4c1(bindings::i2c2B, 0x2C);
    mcp::MCP4461 pot_control_l0n4c2(bindings::i2c2C, 0x2C);
    //neuron 5
    mcp::MCP4461 pot_control_l0n5c0(bindings::i2c2A, 0x2D);
    mcp::MCP4461 pot_control_l0n5c1(bindings::i2c2B, 0x2D);
    mcp::MCP4461 pot_control_l0n5c2(bindings::i2c2C, 0x2D); 
    //neuron 6
    mcp::MCP4461 pot_control_l0n6c0(bindings::i2c2A, 0x2E);
    mcp::MCP4461 pot_control_l0n6c1(bindings::i2c2B, 0x2E);
    mcp::MCP4461 pot_control_l0n6c2(bindings::i2c2C, 0x2E);
    // neuron 7
    mcp::MCP4461 pot_control_l0n7c0(bindings::i2c2A, 0x2F);
    mcp::MCP4461 pot_control_l0n7c1(bindings::i2c2B, 0x2F);
    mcp::MCP4461 pot_control_l0n7c2(bindings::i2c2C, 0x2F);
    
    //bias
    mcp::MCP4461 pot_control_l0n47f(bindings::i2c2D, 0x2D);
    mcp::MCP4461 pot_control_l0n47b(bindings::i2c2D, 0x2C);

    //neuron 4
    mcp::MCP4461 pot_control_l0n8c0(bindings::i2c3A, 0x2C);
    mcp::MCP4461 pot_control_l0n8c1(bindings::i2c3B, 0x2C);
    mcp::MCP4461 pot_control_l0n8c2(bindings::i2c3C, 0x2C);
    //neuron 5
    mcp::MCP4461 pot_control_l0n9c0(bindings::i2c3A, 0x2D);
    mcp::MCP4461 pot_control_l0n9c1(bindings::i2c3B, 0x2D);
    mcp::MCP4461 pot_control_l0n9c2(bindings::i2c3C, 0x2D); 
    //neuron 6
    mcp::MCP4461 pot_control_l0n10c0(bindings::i2c3A, 0x2E);
    mcp::MCP4461 pot_control_l0n10c1(bindings::i2c3B, 0x2E);
    mcp::MCP4461 pot_control_l0n10c2(bindings::i2c3C, 0x2E);
    // neuron 7
    mcp::MCP4461 pot_control_l0n11c0(bindings::i2c3A, 0x2F);
    mcp::MCP4461 pot_control_l0n11c1(bindings::i2c3B, 0x2F);
    mcp::MCP4461 pot_control_l0n11c2(bindings::i2c3C, 0x2F);
    
    //bias
    mcp::MCP4461 pot_control_l0n811f(bindings::i2c3D, 0x2D);
    mcp::MCP4461 pot_control_l0n811b(bindings::i2c3D, 0x2C);




    // // single wn block

    mcp::MCP4728 dac0(bindings::i2c1A, 0x60, 2.75F, -2.75F);
    mcp::MCP4728 dac1(bindings::i2c2A, 0x60, 2.75F, -2.75F);
    mcp::MCP4728 dac2(bindings::i2c3A, 0x60, 2.75F, -2.75F);


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

    // Second block
    DigitalPotentiometer<uint8_t> pot_l0n4w0(pot_control_l0n4c0, 0);
    DigitalPotentiometer<uint8_t> pot_l0n4w1(pot_control_l0n4c0, 1);
    DigitalPotentiometer<uint8_t> pot_l0n4w2(pot_control_l0n4c0, 2);
    DigitalPotentiometer<uint8_t> pot_l0n4w3(pot_control_l0n4c0, 3); 
    DigitalPotentiometer<uint8_t> pot_l0n4w4(pot_control_l0n4c1, 0);
    DigitalPotentiometer<uint8_t> pot_l0n4w5(pot_control_l0n4c1, 1);
    DigitalPotentiometer<uint8_t> pot_l0n4w6(pot_control_l0n4c1, 2);
    DigitalPotentiometer<uint8_t> pot_l0n4w7(pot_control_l0n4c1, 3);
    DigitalPotentiometer<uint8_t> pot_l0n4w8(pot_control_l0n4c2, 0);
    DigitalPotentiometer<uint8_t> pot_l0n4w9(pot_control_l0n4c2, 1);
    DigitalPotentiometer<uint8_t> pot_l0n4w10(pot_control_l0n4c2, 2);
    DigitalPotentiometer<uint8_t> pot_l0n4w11(pot_control_l0n4c2, 3);

    DigitalPotentiometer<uint8_t> pot_l0n5w0(pot_control_l0n5c0, 0);
    DigitalPotentiometer<uint8_t> pot_l0n5w1(pot_control_l0n5c0, 1);
    DigitalPotentiometer<uint8_t> pot_l0n5w2(pot_control_l0n5c0, 2);
    DigitalPotentiometer<uint8_t> pot_l0n5w3(pot_control_l0n5c0, 3); 
    DigitalPotentiometer<uint8_t> pot_l0n5w4(pot_control_l0n5c1, 0);
    DigitalPotentiometer<uint8_t> pot_l0n5w5(pot_control_l0n5c1, 1);
    DigitalPotentiometer<uint8_t> pot_l0n5w6(pot_control_l0n5c1, 2);
    DigitalPotentiometer<uint8_t> pot_l0n5w7(pot_control_l0n5c1, 3);
    DigitalPotentiometer<uint8_t> pot_l0n5w8(pot_control_l0n5c2, 0);
    DigitalPotentiometer<uint8_t> pot_l0n5w9(pot_control_l0n5c2, 1);
    DigitalPotentiometer<uint8_t> pot_l0n5w10(pot_control_l0n5c2, 2);
    DigitalPotentiometer<uint8_t> pot_l0n5w11(pot_control_l0n5c2, 3);

    DigitalPotentiometer<uint8_t> pot_l0n6w0(pot_control_l0n6c0, 0);
    DigitalPotentiometer<uint8_t> pot_l0n6w1(pot_control_l0n6c0, 1);
    DigitalPotentiometer<uint8_t> pot_l0n6w2(pot_control_l0n6c0, 2);
    DigitalPotentiometer<uint8_t> pot_l0n6w3(pot_control_l0n6c0, 3); 
    DigitalPotentiometer<uint8_t> pot_l0n6w4(pot_control_l0n6c1, 0);
    DigitalPotentiometer<uint8_t> pot_l0n6w5(pot_control_l0n6c1, 1);
    DigitalPotentiometer<uint8_t> pot_l0n6w6(pot_control_l0n6c1, 2);
    DigitalPotentiometer<uint8_t> pot_l0n6w7(pot_control_l0n6c1, 3);
    DigitalPotentiometer<uint8_t> pot_l0n6w8(pot_control_l0n6c2, 0);
    DigitalPotentiometer<uint8_t> pot_l0n6w9(pot_control_l0n6c2, 1);
    DigitalPotentiometer<uint8_t> pot_l0n6w10(pot_control_l0n6c2, 2);
    DigitalPotentiometer<uint8_t> pot_l0n6w11(pot_control_l0n6c2, 3);
    
    DigitalPotentiometer<uint8_t> pot_l0n7w0(pot_control_l0n7c0, 0);
    DigitalPotentiometer<uint8_t> pot_l0n7w1(pot_control_l0n7c0, 1);
    DigitalPotentiometer<uint8_t> pot_l0n7w2(pot_control_l0n7c0, 2);
    DigitalPotentiometer<uint8_t> pot_l0n7w3(pot_control_l0n7c0, 3); 
    DigitalPotentiometer<uint8_t> pot_l0n7w4(pot_control_l0n7c1, 0);
    DigitalPotentiometer<uint8_t> pot_l0n7w5(pot_control_l0n7c1, 1);
    DigitalPotentiometer<uint8_t> pot_l0n7w6(pot_control_l0n7c1, 2);
    DigitalPotentiometer<uint8_t> pot_l0n7w7(pot_control_l0n7c1, 3);
    DigitalPotentiometer<uint8_t> pot_l0n7w8(pot_control_l0n7c2, 0);
    DigitalPotentiometer<uint8_t> pot_l0n7w9(pot_control_l0n7c2, 1);
    DigitalPotentiometer<uint8_t> pot_l0n7w10(pot_control_l0n7c2, 2);
    DigitalPotentiometer<uint8_t> pot_l0n7w11(pot_control_l0n7c2, 3);

    DigitalPotentiometer<uint8_t> pot_l0n4b(pot_control_l0n47b, 0);
    DigitalPotentiometer<uint8_t> pot_l0n5b(pot_control_l0n47b, 1);
    DigitalPotentiometer<uint8_t> pot_l0n6b(pot_control_l0n47b, 2);
    DigitalPotentiometer<uint8_t> pot_l0n7b(pot_control_l0n47b, 3); 
    
    DigitalPotentiometer<uint8_t> pot_l0n4f(pot_control_l0n47f, 0);
    DigitalPotentiometer<uint8_t> pot_l0n5f(pot_control_l0n47f, 1);
    DigitalPotentiometer<uint8_t> pot_l0n6f(pot_control_l0n47f, 2);
    DigitalPotentiometer<uint8_t> pot_l0n7f(pot_control_l0n47f, 3);

    // Second block
    DigitalPotentiometer<uint8_t> pot_l0n8w0(pot_control_l0n8c0, 0);
    DigitalPotentiometer<uint8_t> pot_l0n8w1(pot_control_l0n8c0, 1);
    DigitalPotentiometer<uint8_t> pot_l0n8w2(pot_control_l0n8c0, 2);
    DigitalPotentiometer<uint8_t> pot_l0n8w3(pot_control_l0n8c0, 3); 
    DigitalPotentiometer<uint8_t> pot_l0n8w4(pot_control_l0n8c1, 0);
    DigitalPotentiometer<uint8_t> pot_l0n8w5(pot_control_l0n8c1, 1);
    DigitalPotentiometer<uint8_t> pot_l0n8w6(pot_control_l0n8c1, 2);
    DigitalPotentiometer<uint8_t> pot_l0n8w7(pot_control_l0n8c1, 3);
    DigitalPotentiometer<uint8_t> pot_l0n8w8(pot_control_l0n8c2, 0);
    DigitalPotentiometer<uint8_t> pot_l0n8w9(pot_control_l0n8c2, 1);
    DigitalPotentiometer<uint8_t> pot_l0n8w10(pot_control_l0n8c2, 2);
    DigitalPotentiometer<uint8_t> pot_l0n8w11(pot_control_l0n8c2, 3);

    DigitalPotentiometer<uint8_t> pot_l0n9w0(pot_control_l0n9c0, 0);
    DigitalPotentiometer<uint8_t> pot_l0n9w1(pot_control_l0n9c0, 1);
    DigitalPotentiometer<uint8_t> pot_l0n9w2(pot_control_l0n9c0, 2);
    DigitalPotentiometer<uint8_t> pot_l0n9w3(pot_control_l0n9c0, 3); 
    DigitalPotentiometer<uint8_t> pot_l0n9w4(pot_control_l0n9c1, 0);
    DigitalPotentiometer<uint8_t> pot_l0n9w5(pot_control_l0n9c1, 1);
    DigitalPotentiometer<uint8_t> pot_l0n9w6(pot_control_l0n9c1, 2);
    DigitalPotentiometer<uint8_t> pot_l0n9w7(pot_control_l0n9c1, 3);
    DigitalPotentiometer<uint8_t> pot_l0n9w8(pot_control_l0n9c2, 0);
    DigitalPotentiometer<uint8_t> pot_l0n9w9(pot_control_l0n9c2, 1);
    DigitalPotentiometer<uint8_t> pot_l0n9w10(pot_control_l0n9c2, 2);
    DigitalPotentiometer<uint8_t> pot_l0n9w11(pot_control_l0n9c2, 3);

    DigitalPotentiometer<uint8_t> pot_l0n10w0(pot_control_l0n10c0, 0);
    DigitalPotentiometer<uint8_t> pot_l0n10w1(pot_control_l0n10c0, 1);
    DigitalPotentiometer<uint8_t> pot_l0n10w2(pot_control_l0n10c0, 2);
    DigitalPotentiometer<uint8_t> pot_l0n10w3(pot_control_l0n10c0, 3); 
    DigitalPotentiometer<uint8_t> pot_l0n10w4(pot_control_l0n10c1, 0);
    DigitalPotentiometer<uint8_t> pot_l0n10w5(pot_control_l0n10c1, 1);
    DigitalPotentiometer<uint8_t> pot_l0n10w6(pot_control_l0n10c1, 2);
    DigitalPotentiometer<uint8_t> pot_l0n10w7(pot_control_l0n10c1, 3);
    DigitalPotentiometer<uint8_t> pot_l0n10w8(pot_control_l0n10c2, 0);
    DigitalPotentiometer<uint8_t> pot_l0n10w9(pot_control_l0n10c2, 1);
    DigitalPotentiometer<uint8_t> pot_l0n10w10(pot_control_l0n10c2, 2);
    DigitalPotentiometer<uint8_t> pot_l0n10w11(pot_control_l0n10c2, 3);
    
    DigitalPotentiometer<uint8_t> pot_l0n11w0(pot_control_l0n11c0, 0);
    DigitalPotentiometer<uint8_t> pot_l0n11w1(pot_control_l0n11c0, 1);
    DigitalPotentiometer<uint8_t> pot_l0n11w2(pot_control_l0n11c0, 2);
    DigitalPotentiometer<uint8_t> pot_l0n11w3(pot_control_l0n11c0, 3); 
    DigitalPotentiometer<uint8_t> pot_l0n11w4(pot_control_l0n11c1, 0);
    DigitalPotentiometer<uint8_t> pot_l0n11w5(pot_control_l0n11c1, 1);
    DigitalPotentiometer<uint8_t> pot_l0n11w6(pot_control_l0n11c1, 2);
    DigitalPotentiometer<uint8_t> pot_l0n11w7(pot_control_l0n11c1, 3);
    DigitalPotentiometer<uint8_t> pot_l0n11w8(pot_control_l0n11c2, 0);
    DigitalPotentiometer<uint8_t> pot_l0n11w9(pot_control_l0n11c2, 1);
    DigitalPotentiometer<uint8_t> pot_l0n11w10(pot_control_l0n11c2, 2);
    DigitalPotentiometer<uint8_t> pot_l0n11w11(pot_control_l0n11c2, 3);

    DigitalPotentiometer<uint8_t> pot_l0n8b(pot_control_l0n811b, 0);
    DigitalPotentiometer<uint8_t> pot_l0n9b(pot_control_l0n811b, 1);
    DigitalPotentiometer<uint8_t> pot_l0n10b(pot_control_l0n811b, 2);
    DigitalPotentiometer<uint8_t> pot_l0n11b(pot_control_l0n811b, 3); 
    
    DigitalPotentiometer<uint8_t> pot_l0n8f(pot_control_l0n811f, 0);
    DigitalPotentiometer<uint8_t> pot_l0n9f(pot_control_l0n811f, 1);
    DigitalPotentiometer<uint8_t> pot_l0n10f(pot_control_l0n811f, 2);
    DigitalPotentiometer<uint8_t> pot_l0n11f(pot_control_l0n811f, 3);

}  // namespace device


namespace bindings {
shared::periph::DigitalOutput& red_led = mcal::red_led;
shared::periph::DigitalOutput& green_led = mcal::green_led;
shared::periph::DigitalOutput& heartbeat = mcal::heartbeat;

shared::periph::I2CBus& i2c1 = mcal::i2c1;
shared::periph::I2CBus& i2c2 = mcal::i2c2;
shared::periph::I2CBus& i2c3 = mcal::i2c3;



shared::periph::I2CBus& i2c1A = device::i2c_channels[0][0];
shared::periph::I2CBus& i2c1B = device::i2c_channels[0][1];
shared::periph::I2CBus& i2c1C = device::i2c_channels[0][2];
shared::periph::I2CBus& i2c1D = device::i2c_channels[0][3];


shared::periph::I2CBus& i2c2A = device::i2c_channels[1][0];
shared::periph::I2CBus& i2c2B = device::i2c_channels[1][1];
shared::periph::I2CBus& i2c2C = device::i2c_channels[1][2];
shared::periph::I2CBus& i2c2D = device::i2c_channels[1][3];

shared::periph::I2CBus& i2c3A = device::i2c_channels[2][0];
shared::periph::I2CBus& i2c3B = device::i2c_channels[2][1];
shared::periph::I2CBus& i2c3C = device::i2c_channels[2][2];
shared::periph::I2CBus& i2c3D = device::i2c_channels[2][3];

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
    },
    {
        device::pot_l0n4w0,
        device::pot_l0n4w1,
        device::pot_l0n4w2,
        device::pot_l0n4w3,
        device::pot_l0n4w4,
        device::pot_l0n4w5,
        device::pot_l0n4w6,
        device::pot_l0n4w7,
        device::pot_l0n4w8,
        device::pot_l0n4w9,
        device::pot_l0n4w10,
        device::pot_l0n4w11
    },
    {
        device::pot_l0n5w0,
        device::pot_l0n5w1,
        device::pot_l0n5w2,
        device::pot_l0n5w3,
        device::pot_l0n5w4,
        device::pot_l0n5w5,
        device::pot_l0n5w6,
        device::pot_l0n5w7,
        device::pot_l0n5w8,
        device::pot_l0n5w9,
        device::pot_l0n5w10,
        device::pot_l0n5w11
    },
    {
        device::pot_l0n6w0,
        device::pot_l0n6w1,
        device::pot_l0n6w2,
        device::pot_l0n6w3,
        device::pot_l0n6w4,
        device::pot_l0n6w5,
        device::pot_l0n6w6,
        device::pot_l0n6w7,
        device::pot_l0n6w8,
        device::pot_l0n6w9,
        device::pot_l0n6w10,
        device::pot_l0n6w11
    },
    {
        device::pot_l0n7w0,
        device::pot_l0n7w1,
        device::pot_l0n7w2,
        device::pot_l0n7w3,
        device::pot_l0n7w4,
        device::pot_l0n7w5,
        device::pot_l0n7w6,
        device::pot_l0n7w7,
        device::pot_l0n7w8,
        device::pot_l0n7w9,
        device::pot_l0n7w10,
        device::pot_l0n7w11
    },
    {
        device::pot_l0n8w0,
        device::pot_l0n8w1,
        device::pot_l0n8w2,
        device::pot_l0n8w3,
        device::pot_l0n8w4,
        device::pot_l0n8w5,
        device::pot_l0n8w6,
        device::pot_l0n8w7,
        device::pot_l0n8w8,
        device::pot_l0n8w9,
        device::pot_l0n8w10,
        device::pot_l0n8w11
    },
    {
        device::pot_l0n9w0,
        device::pot_l0n9w1,
        device::pot_l0n9w2,
        device::pot_l0n9w3,
        device::pot_l0n9w4,
        device::pot_l0n9w5,
        device::pot_l0n9w6,
        device::pot_l0n9w7,
        device::pot_l0n9w8,
        device::pot_l0n9w9,
        device::pot_l0n9w10,
        device::pot_l0n9w11
    },
    {
        device::pot_l0n10w0,
        device::pot_l0n10w1,
        device::pot_l0n10w2,
        device::pot_l0n10w3,
        device::pot_l0n10w4,
        device::pot_l0n10w5,
        device::pot_l0n10w6,
        device::pot_l0n10w7,
        device::pot_l0n10w8,
        device::pot_l0n10w9,
        device::pot_l0n10w10,
        device::pot_l0n10w11
    },
    {
        device::pot_l0n11w0,
        device::pot_l0n11w1,
        device::pot_l0n11w2,
        device::pot_l0n11w3,
        device::pot_l0n11w4,
        device::pot_l0n11w5,
        device::pot_l0n11w6,
        device::pot_l0n11w7,
        device::pot_l0n11w8,
        device::pot_l0n11w9,
        device::pot_l0n11w10,
        device::pot_l0n11w11
    }
}};

std::array<shared::device::DigitalPotentiometer<uint8_t>, kNumNeuronsPerLayer> bias_pots = {
    device::pot_l0n0b,
    device::pot_l0n1b,
    device::pot_l0n2b,
    device::pot_l0n3b,
    device::pot_l0n4b,
    device::pot_l0n5b,
    device::pot_l0n6b,
    device::pot_l0n7b,
    device::pot_l0n8b,
    device::pot_l0n9b,
    device::pot_l0n10b,
    device::pot_l0n11b
};

std::array<shared::device::DigitalPotentiometer<uint8_t>, kNumNeuronsPerLayer> fb_pots = {
    device::pot_l0n0f,
    device::pot_l0n1f,
    device::pot_l0n2f,
    device::pot_l0n3f,
    device::pot_l0n4f,
    device::pot_l0n5f,
    device::pot_l0n6f,
    device::pot_l0n7f,
    device::pot_l0n8f,
    device::pot_l0n9f,
    device::pot_l0n10f,
    device::pot_l0n11f
};

shared::periph::AnalogOutputGroup<kNumAnalogOutputs>& analog_output_group_0 = device::dac0;
shared::periph::AnalogOutputGroup<kNumAnalogOutputs>& analog_output_group_1 = device::dac1;
shared::periph::AnalogOutputGroup<kNumAnalogOutputs>& analog_output_group_2 = device::dac2;



void Init() {
    SystemClock_Config();
    HAL_Init();
    MX_GPIO_Init();
    MX_USART3_UART_Init();
    
    MX_I2C1_Init();
    MX_I2C2_Init();
    MX_I2C3_Init();

    SetDebugUART(mcal::debug_uart);
    device::dac0.SetChannelVoltageReference();
    device::dac1.SetChannelVoltageReference();
    device::dac2.SetChannelVoltageReference();

    std::cout << "Begin" << std::endl;

}

void DelayMs(uint32_t ms)
{
    HAL_Delay(ms);
}

}  // namespace bindings
