#pragma once

#include "shared/periph/analog_input.hpp"
#include "shared/periph/analog_output.hpp"
#include "shared/periph/gpio.hpp"
#include "shared/periph/pwm.hpp"
#include "shared/periph/i2c.hpp"

namespace bindings {

constexpr uint8_t kNumAnalogOutputs = 4;

extern shared::periph::DigitalOutput& red_led;
extern shared::periph::DigitalOutput& green_led;
extern shared::periph::DigitalOutput& blue_led;

extern shared::periph::I2CBus& i2c1;
extern shared::periph::I2CBus& i2c2;
extern shared::periph::I2CBus& i2c3;

extern shared::periph::I2CBus& i2c1A;
extern shared::periph::I2CBus& i2c1B;
extern shared::periph::I2CBus& i2c1C;
extern shared::periph::I2CBus& i2c1D;
extern shared::periph::I2CBus& i2c1E;
extern shared::periph::I2CBus& i2c1F;
extern shared::periph::I2CBus& i2c1G;
extern shared::periph::I2CBus& i2c1H;
extern shared::periph::I2CBus& i2c2A;
extern shared::periph::I2CBus& i2c2B;
extern shared::periph::I2CBus& i2c2C;
extern shared::periph::I2CBus& i2c2D;
extern shared::periph::I2CBus& i2c2E;
extern shared::periph::I2CBus& i2c2F;
extern shared::periph::I2CBus& i2c2G;
extern shared::periph::I2CBus& i2c2H;
extern shared::periph::I2CBus& i2c3A;
extern shared::periph::I2CBus& i2c3B;
extern shared::periph::I2CBus& i2c3C;
extern shared::periph::I2CBus& i2c3D;
extern shared::periph::I2CBus& i2c3E;
extern shared::periph::I2CBus& i2c3F;
extern shared::periph::I2CBus& i2c3G;
extern shared::periph::I2CBus& i2c3H;

extern shared::periph::AnalogOutputGroup<kNumAnalogOutputs>&
    analog_output_group;

extern void DelayMs(uint32_t ms);
extern void Init();

}  // namespace bindings