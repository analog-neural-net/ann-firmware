#include <cstdint>

#include "shared/comms/i2c/msg.hpp"
#include "shared/device/dac.hpp"
#include "shared/periph/i2c.hpp"

namespace shared::device::mcp {
constexpr uint8_t kMcp4728NumChannels = 4;

class MCP4728 : public DigitalAnalogConverter<kMcp4728NumChannels> {
private:
    enum class VoltageRef {
        VDD = 0,
        INTERNAL = 1
    };

public:
    MCP4728(periph::I2CBus& i2c, uint8_t address, float vref, float vmin)
        : i2c_(i2c), address_(address), vref_(vref), vmin_(vmin) {
        // can be overridden using SetVref if needed
        SetChannelVoltageReference(VoltageRef::VDD, VoltageRef::VDD,
                                   VoltageRef::VDD, VoltageRef::VDD);
    }

    void SetVoltage(uint8_t channel, float voltage) override {
        if (channel >= kMcp4728NumChannels) {
            return;
        }

        // Convert voltage to DAC value (12-bit)
        uint16_t dac_value = VoltageToDacCode(voltage);
        // Store voltage for GetVoltageSetpoint
        voltage_setpoints_[channel] = voltage;

        // Store DAC value to be written on LoadVoltages
        channel_values_[channel] = dac_value;
    }

    float GetVoltageSetpoint(uint8_t channel) override {
        if (channel >= kMcp4728NumChannels) {
            return 0.0F;
        }
        return voltage_setpoints_[channel];
    }

    float GetLoadedVoltage(uint8_t channel) override {
        if (channel >= kMcp4728NumChannels) {
            return 0.0F;
        }
        return loaded_voltages_[channel];
    }

    void LoadVoltages() override {
        // Sequential write to all channels
        uint8_t data[2 * kMcp4728NumChannels];  // two bytes per channel
        for (uint8_t i = 0; i < kMcp4728NumChannels; i++) {
            // Upper data byte: 0b0000 + upper 8 bits of 12-bit DAC value
            data[i * 2] = static_cast<uint8_t>(channel_values_[i] >> 8);
            // Lower data byte: lower 4 bits of 12-bit DAC value + 0000
            data[i * 2 + 1] = static_cast<uint8_t>(channel_values_[i] & 0xFF);
        }

        i2c::Message msg(address_, data, i2c::MessageType::Write);
        i2c_.Write(msg);

        // Update loaded voltages
        for (uint8_t i = 0; i < kMcp4728NumChannels; i++) {
            loaded_voltages_[i] = voltage_setpoints_[i];
        }
    }

    void SetAndLoadAllVoltages(float voltages[kMcp4728NumChannels]) override {
        for (uint8_t i = 0; i < kMcp4728NumChannels; i++) {
            SetVoltage(i, voltages[i]);
        }
        LoadVoltages();
    }

    void SetChannelVoltageReference(VoltageRef chan_a = VoltageRef::VDD, VoltageRef chan_b = VoltageRef::VDD,
        VoltageRef chan_c = VoltageRef::VDD, VoltageRef chan_d = VoltageRef::VDD) {
            uint8_t vrefCfgByte[1];
            vrefCfgByte[0] = kMcp4728CfgVref | (static_cast<uint8_t>(chan_a) << 3) |
            (static_cast<uint8_t>(chan_b) << 2) |
            (static_cast<uint8_t>(chan_c) << 1) |
            static_cast<uint8_t>(chan_d);
            i2c::Message msg(address_, vrefCfgByte, i2c::MessageType::Write);
            i2c_.Write(msg);
}


private:
    static constexpr uint16_t kMaxValue = 4095;  // 12-bit resolution
    static constexpr uint8_t kMcp4728CfgVref = 0x80;

    periph::I2CBus& i2c_;
    uint8_t address_;

    float vref_;
    float vmin_;

    uint16_t channel_values_[kMcp4728NumChannels] = {0};
    float voltage_setpoints_[kMcp4728NumChannels] = {0.0F};
    float loaded_voltages_[kMcp4728NumChannels] = {0.0F};

    uint16_t VoltageToDacCode(float voltage) {
        if (voltage < vmin_) {
            return 0;
        }
        if (voltage > vref_) {
            return kMaxValue;
        }

        return static_cast<uint16_t>((voltage - vmin_) / (vref_ - vmin_) *
                                     (float)kMaxValue);
    }

    
};

}  // namespace shared::device::mcp
