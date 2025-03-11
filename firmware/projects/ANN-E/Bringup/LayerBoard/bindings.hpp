#pragma once


#include "shared/periph/analog_input.hpp"
#include "shared/periph/analog_output.hpp"
#include "shared/periph/gpio.hpp"
#include "shared/periph/pwm.hpp"
#include "shared/periph/i2c.hpp"
#include "shared/device/digital_pot.hpp"

namespace bindings {

constexpr uint8_t kNumAnalogOutputs = 4;
constexpr uint8_t kNumi2cBuses = 3;
constexpr uint8_t kNumi2cChannelsPerBus = 8;


constexpr uint8_t kNumLayers = 2;
constexpr uint8_t kNumWeightsPerNeuron = 12;

//needs only be the max size, of any layer, becasue we can afford to allocate the extra space currently
constexpr uint8_t kNumNeuronsPerLayer = 12;



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

extern std::array<std::array<std::array<shared::device::DigitalPotentiometer<uint8_t>, kNumWeightsPerNeuron>, bindings::kNumNeuronsPerLayer>, bindings::kNumLayers> pots;
// extern std::array<std::array<shared::device::DigitalPotentiometer<uint8_t>, kNumWeightsPerNeuron>, bindings::kNumNeuronsPerLayer> pots;

extern std::array<std::array<shared::device::DigitalPotentiometer<uint8_t>, bindings::kNumNeuronsPerLayer>, bindings::kNumLayers> bias_pots;
extern std::array<std::array<shared::device::DigitalPotentiometer<uint8_t>, bindings::kNumNeuronsPerLayer>, bindings::kNumLayers> fb_pots;

extern void DelayMs(uint32_t ms);
extern void Init();

}  // namespace bindings