#pragma once


#include "shared/periph/analog_input.hpp"
#include "shared/periph/analog_output.hpp"
#include "shared/periph/analog_input.hpp"

#include "shared/periph/gpio.hpp"
#include "shared/periph/pwm.hpp"
#include "shared/periph/i2c.hpp"
#include "shared/device/digital_pot.hpp"
#include "shared/periph/uart.hpp"

namespace bindings {
constexpr uint8_t kNumAnalogInputs = 12;

constexpr uint8_t kNumAnalogOutputs = 4;
constexpr uint8_t kNumi2cBuses = 3;
constexpr uint8_t kNumi2cChannelsPerBus = 8;

constexpr uint8_t kOutputLayerSize = 10;

constexpr uint8_t kNumLayers = 2;
constexpr uint8_t kNumWeightsPerNeuron = 12;

//needs only be the max size, of any layer, becasue we can afford to allocate the extra space currently
constexpr uint8_t kNumNeuronsPerLayer = 12;
constexpr uint8_t kNumNeuronsPerLayerOutput = 10;


extern shared::periph::DigitalOutput& red_led;
extern shared::periph::DigitalOutput& green_led;
extern shared::periph::DigitalOutput& blue_led;
extern shared::periph::UartBus& uart_bus;


extern shared::periph::I2CBus& i2c1;
extern shared::periph::I2CBus& i2c2;
extern shared::periph::I2CBus& i2c3;


extern shared::periph::AnalogInput& analog_input_0;
extern shared::periph::AnalogInput& analog_input_1;
extern shared::periph::AnalogInput& analog_input_2;
extern shared::periph::AnalogInput& analog_input_3;
extern shared::periph::AnalogInput& analog_input_4;
extern shared::periph::AnalogInput& analog_input_5;
extern shared::periph::AnalogInput& analog_input_6;
extern shared::periph::AnalogInput& analog_input_7;
extern shared::periph::AnalogInput& analog_input_8;
extern shared::periph::AnalogInput& analog_input_9;

extern shared::periph::AnalogInput* adc_channels[kOutputLayerSize];

extern shared::periph::AnalogOutputGroup<kNumAnalogOutputs>&
    analog_output_group_0;

extern shared::periph::AnalogOutputGroup<kNumAnalogOutputs>&
    analog_output_group_1;

extern shared::periph::AnalogOutputGroup<kNumAnalogOutputs>&
    analog_output_group_2;

extern std::array<std::array<std::array<shared::device::DigitalPotentiometer<uint8_t>, kNumWeightsPerNeuron>, bindings::kNumNeuronsPerLayer>, bindings::kNumLayers> pots;
// extern std::array<std::array<shared::device::DigitalPotentiometer<uint8_t>, kNumWeightsPerNeuron>, bindings::kNumNeuronsPerLayer> pots;

extern std::array<std::array<shared::device::DigitalPotentiometer<uint8_t>, bindings::kNumNeuronsPerLayer>, bindings::kNumLayers> bias_pots;
extern std::array<std::array<shared::device::DigitalPotentiometer<uint8_t>, bindings::kNumNeuronsPerLayer>, bindings::kNumLayers> fb_pots;

extern uint32_t GetTimeMs();
extern void DelayMs(uint32_t ms);
extern void Init();

}  // namespace bindings