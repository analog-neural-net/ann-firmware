#pragma once

#include "shared/periph/i2c.hpp"
#include "shared/device/dac.hpp"


#define MCP4728_DAC_RESOLUTION 12
namespace shared::device::mcp {


class MCP4728 : public DigitalAnalogConverter {
private:
    shared::periph::I2CBus& i2c_bus_;
    uint8_t dac_i2c_address_;

    void writeSingleChannel();
    void fastWriteAllChannels(uint16_t &dac_codes[MCP4728_DAC_RESOLUTION]);
    void configVref();
    void readDAC();
    
public:
    MCP4728(shared::periph::I2CBus& i2c_bus, uint8_t dac_address, float min_voltage, float ref_voltage)
        : i2c_bus_(i2c_bus), dac_i2c_address_(dac_address) {
            min_voltage_ = min_voltage;
            ref_voltage_ = ref_voltage;
            dac_resolution_ = MCP4728_DAC_RESOLUTION;
        }

    void SetVoltage(uint8_t channel, float voltage) override {
        uint16_t dac_value = (uint16_t)((voltage - min_voltage_) / ref_voltage_ *  (float)(1 << dac_resolution_));
    }

    float GetVoltageOutput(uint8_t channel) override {

    }

}

}