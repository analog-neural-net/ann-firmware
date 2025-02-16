#pragma once

#include "inc/network_params.hpp"
#include "projects/ANN-E/Motherboard/inc/network_params.hpp"
#include "shared/periph/analog_input.hpp"
#include "shared/periph/analog_output.hpp"
#include "shared/periph/can.hpp"
#include "shared/periph/gpio.hpp"
#include "shared/periph/i2c.hpp"
#include "shared/periph/uart.hpp"

namespace bindings {

extern shared::periph::AnalogInputGroup<kNumNetworkOutputs>& network_results;
extern shared::periph::AnalogOutputGroup<kNumNetworkInputs>& network_inputs;

extern shared::periph::AnalogInput& current_sense_5v5;
extern shared::periph::DigitalOutput& ready_for_uart_command;

extern shared::periph::UartBus& uart_bus1;

extern shared::periph::I2CBus& i2c_bus1;
extern shared::periph::I2CBus& i2c_bus2;
extern shared::periph::I2CBus& i2c_bus3;

extern shared::periph::I2CBus& i2c_bus1A;
extern shared::periph::I2CBus& i2c_bus1B;
extern shared::periph::I2CBus& i2c_bus1C;
extern shared::periph::I2CBus& i2c_bus1D;
extern shared::periph::I2CBus& i2c_bus1E;
extern shared::periph::I2CBus& i2c_bus1F;
extern shared::periph::I2CBus& i2c_bus1G;
extern shared::periph::I2CBus& i2c_bus1H;

extern shared::periph::I2CBus& i2c_bus2A;
extern shared::periph::I2CBus& i2c_bus2B;
extern shared::periph::I2CBus& i2c_bus2C;
extern shared::periph::I2CBus& i2c_bus2D;
extern shared::periph::I2CBus& i2c_bus2E;
extern shared::periph::I2CBus& i2c_bus2F;
extern shared::periph::I2CBus& i2c_bus2G;
extern shared::periph::I2CBus& i2c_bus2H;

extern shared::periph::I2CBus& i2c_bus3A;
extern shared::periph::I2CBus& i2c_bus3B;
extern shared::periph::I2CBus& i2c_bus3C;
extern shared::periph::I2CBus& i2c_bus3D;
extern shared::periph::I2CBus& i2c_bus3E;
extern shared::periph::I2CBus& i2c_bus3F;
extern shared::periph::I2CBus& i2c_bus3G;
extern shared::periph::I2CBus& i2c_bus3H;

extern void Initialize();
}  // namespace bindings
