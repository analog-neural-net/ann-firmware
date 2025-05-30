#pragma once

#include <cstdint>

#include "shared/comms/i2c/msg.hpp"
#include "shared/device/digital_pot.hpp"
#include "shared/periph/i2c.hpp"

#include <iostream>

namespace shared::device::mcp {

class MCP4461 : public DigitalPotentiometerController<uint8_t> {
private:
    // Register addresses
    enum class Register : uint8_t {
        WIPER0 = 0x00,
        WIPER1 = 0x01,
        WIPER2 = 0x06,
        WIPER3 = 0x07,
        TCON0 = 0x04,
        TCON1 = 0x0A,
    };
    constexpr static uint8_t POT_INCREMENT = 0b01 << 2;
    constexpr static uint8_t POT_DECREMENT = 0b10 << 2;
    constexpr static uint8_t POT_READ = 0b11 << 2;


public:
    MCP4461(periph::I2CBus& i2c, uint8_t i2c_addr)
        : i2c_(&i2c), device_addr_(i2c_addr) {}

    MCP4461(): i2c_(nullptr), device_addr_(0x2C) {}

    void SetPosition(uint8_t pot_index, uint8_t position) override {
        if (pot_index >= kNumPots) {
            return;
        }

        Register reg = GetWiperReg(pot_index);
        WriteRegister(reg, position);
    }

    uint8_t GetPosition(uint8_t pot_index) override {
        if (pot_index >= kNumPots) {
            return 0;
        }

        Register reg = GetWiperReg(pot_index);
        return ReadRegister(reg);
    }

    bool GetTerminalConnection(uint8_t pot_index,
                               DigitalPotTerminal terminal) override {
        if (pot_index >= kNumPots) {
            return false;
        }

        bool terminal_a, terminal_b, terminal_w;
        GetTerminalConnections(pot_index, &terminal_a, &terminal_b,
                               &terminal_w);

        switch (terminal) {
            case DigitalPotTerminal::A:
                return terminal_a;
            case DigitalPotTerminal::B:
                return terminal_b;
            case DigitalPotTerminal::W:
                return terminal_w;
            default:
                return false;
        }
    }

    void GetTerminalConnections(uint8_t pot_index, bool* terminal_connected_a,
                                bool* terminal_connected_b,
                                bool* terminal_connected_w) override {
        if (pot_index >= kNumPots) {
            return;
        }

        Register tcon_reg = (pot_index < 2) ? Register::TCON0 : Register::TCON1;
        uint8_t tcon = ReadRegister(tcon_reg);
        uint8_t shift = (pot_index % 2) * 4;

        *terminal_connected_a = tcon & (0x04 << shift);
        *terminal_connected_w = tcon & (0x02 << shift);
        *terminal_connected_b = tcon & (0x01 << shift);
    }

    void SetTerminalConnections(uint8_t pot_index, bool terminal_connect_a,
                                bool terminal_connect_b,
                                bool terminal_connect_w) override {
        if (pot_index >= kNumPots) {
            return;
        }

        Register tcon_reg = (pot_index < 2) ? Register::TCON0 : Register::TCON1;
        uint8_t shift = (pot_index % 2) * 4;
        uint8_t mask = 0xF << shift;
        // TODO: add shutdown pin configurability
        uint8_t value = (0x8 | (terminal_connect_a << 2) |
                         (terminal_connect_w << 1) | (terminal_connect_b))
                        << shift;

        // Read-modify-write TCON register
        uint8_t tcon = ReadRegister(tcon_reg);
        tcon = (tcon & ~mask) | (value & mask);
        WriteRegister(tcon_reg, tcon);
    }

    void SetTerminalConnection(uint8_t pot_index, DigitalPotTerminal terminal,
                               bool terminal_connect) override {
        if (pot_index >= kNumPots) {
            return;
        }

        bool terminal_a, terminal_b, terminal_w;
        GetTerminalConnections(pot_index, &terminal_a, &terminal_b,
                               &terminal_w);

        switch (terminal) {
            case DigitalPotTerminal::A:
                terminal_a = terminal_connect;
                break;
            case DigitalPotTerminal::B:
                terminal_b = terminal_connect;
                break;
            case DigitalPotTerminal::W:
                terminal_w = terminal_connect;
                break;
            default:
                return;
        }

        SetTerminalConnections(pot_index, terminal_a, terminal_b, terminal_w);
    }

    void IncrementPosition(uint8_t pot_index) override {
        if (pot_index >= kNumPots) {
            return;
        }
        Register reg = GetWiperReg(pot_index);
        IncrementRegister(reg);
    }

    void DecrementPosition(uint8_t pot_index) override {
        if (pot_index >= kNumPots) {
            return;
        }
        Register reg = GetWiperReg(pot_index);
        DecrementRegister(reg);
    }

private:
    // MCP4461 using 8-bit resolution (0-255)
    static constexpr uint8_t kMaxPosition = 255;
    static constexpr uint8_t kNumPots = 4;

    periph::I2CBus* i2c_;
    const uint8_t device_addr_;

    Register GetWiperReg(uint8_t pot_index) {
        Register regs[] = {Register::WIPER0, Register::WIPER1, Register::WIPER2,
                           Register::WIPER3};
        return regs[pot_index];
    }

    void WriteRegister(Register reg, uint8_t value) {
        // MCP4461 uses 8-bit command + 8-bit data format in a single write
        uint8_t reg_write[] = {
            static_cast<uint8_t>(static_cast<uint8_t>(reg) << 4), value};

        i2c::Message msg =
            i2c::Message(device_addr_, reg_write, i2c::MessageType::Write);
        i2c_->Write(msg);
    }

    uint8_t ReadRegister(Register reg) {
        uint8_t cmd[] = {
            static_cast<uint8_t>((static_cast<uint8_t>(reg) << 4) | POT_READ)};
        uint8_t data[2] = {};

        i2c::Message msg1 =
            i2c::Message(device_addr_, cmd, i2c::MessageType::Write);
        i2c::Message msg2 =
            i2c::Message(device_addr_, data, i2c::MessageType::Read);

        i2c_->Write(msg1);
        i2c_->Read(msg2);

        // Data is returned as 2 bytes, but for 8-bit resoultion the MSB,
        // (data[0]) is empty
        return data[1];
    }

    void IncrementRegister(Register reg) {
        uint8_t cmd[] = {
            static_cast<uint8_t>((static_cast<uint8_t>(reg) << 4) | POT_INCREMENT)};
        i2c::Message msg =
            i2c::Message(device_addr_, cmd, i2c::MessageType::Write);
        i2c_->Write(msg);
    }

    void DecrementRegister(Register reg) {
        uint8_t cmd[] = {
            static_cast<uint8_t>((static_cast<uint8_t>(reg) << 4) | POT_DECREMENT)};
        i2c::Message msg =
            i2c::Message(device_addr_, cmd, i2c::MessageType::Write);
        i2c_->Write(msg);
    }
};

}  // namespace shared::device::mcp
