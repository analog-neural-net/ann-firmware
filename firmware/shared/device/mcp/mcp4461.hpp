#pragma once

#include <concepts>

#include "shared/periph/i2c.hpp"
#include "shared/comms/i2c/msg.hpp"
#include "shared/device/digital_pot.hpp"

#include <stdint.h>

namespace shared::device::mcp {

enum class MCP4461Wiper : uint8_t {
    WIPER0 = 0x00,
    WIPER1 = 0x01,
    WIPER2 = 0x06,
    WIPER3 = 0x07,
};

enum class MCP4461TCONReg : uint8_t {
    TCON0 = 0x4,
    TCON1 = 0xA
}; 

enum class MCP4461TCONTerminal : uint8_t {
    TERMINAL_A = 0x2,
    TERMINAL_W = 0x1,
    TERMINAL_B = 0x0
};

enum class MCP4461TCONOffset : uint8_t {
    OFFSET_A = 0x4,
    OFFSET_B = 0x0
};

enum class MCP4461Command : uint8_t {
    WRITE_REGISTER = 0x00,
    INCREMENT_REG = 0x01,
    DECREMENT_REG = 0x02,
    READ_REGISTER = 0x03
};

// Define the concept
template <typename T>
concept MCP4461Register = std::is_same_v<T, MCP4461TCONReg> || std::is_same_v<T, MCP4461Wiper>;

class MCP4461 : public DigitalPotentiometerController<MCP4461Wiper, uint8_t> {
private:

    void writeRegister(MCP4461Register reg, uint8_t data) {
        i2c::Message msg;
        uint8_t transmission[2];
        transmission[0] = (static_cast<uint8_t>(reg) << 4) | (static_cast<uint8_t>(MCP4461Command::WRITE_REGISTER) << 2);
        
        transmission[1] = data;

        msg = i2c::Message(pot_i2c_address_, transmission, i2c::MessageType::Write);
        i2c_bus_.Write(msg);
    }

    uint8_t readRegister(MCP4461Register reg) {
        
        uint8_t transmission_request = (static_cast<uint8_t>(reg) << 4) | (static_cast<uint8_t>(MCP4461Command::READ_REGISTER) << 2);
        uint8_t read_data[2];

        i2c::Message request  = i2c::Message(pot_i2c_address_, transmission_request, i2c::MessageType::Write);
        i2c::Message readback = i2c::Message(pot_i2c_address_, read_data, i2c::MessageType::Read);

        i2c_bus_.Write(request);
        i2c_bus_.Read(readback);

        return read_data[1]; //the MSB is empty/unused in this case
    }
public:
    enum class Terminal : uint8_t {
        TERMINAL_A = 0x2,
        TERMINAL_W = 0x1,
        TERMINAL_B = 0x0
    };

    void SetPosition(MCP4461Wiper pot_index, uint8_t position) override {
        writeRegister(pot_index, position);
    }

    uint8_t GetPosition(MCP4461Wiper pot_index) override {
        return readRegister(pot_index);
    }

    uint8_t GetWiperTerminalConfig(MCP4461Wiper pot_index)  {
        MCP4461TCONReg tcon_register_index = pot_index == MCP4461Wiper::WIPER0 || pot_index == MCP4461Wiper::WIPER1 ? MCP4461TCONReg::TCON0 : MCP4461TCONReg::TCON1;
        uint8_t TCON_readback = readRegister(tcon_register_index);
        return pot_index == MCP4461Wiper::WIPER0 || pot_index == MCP4461Wiper::WIPER2 ? TCON_readback & 0x0F : TCON_readback >> 4;
    }

    bool GetTerminalConnection(MCP4461Wiper pot_index, Terminal terminal) override {
        //get corresponding TCOn Register
        //TCON0[7:0] = Wiper 1[3:0], Wiper0[3:0]
        //TCON1[7:0] = Wiper 3[3:0], Wiper2[3:0]
        //each TCON[3:0] = [1b' shutdown, 1b' terminal A, 1b' terminal W, 1b' terminal B]
        uint8_t pot_config = GetWiperTerminalConfig(pot_index);
        return (bool) (pot_config >> static_cast<uint8_t>(terminal)) & 0x01;
    }   

    void SetTerminalConnections(MCP4461Wiper pot_index, bool terminalConnectedA, bool terminalConnectedB, bool terminalConnectedW) override {
        MCP4461TCONReg tcon_register_index = pot_index == MCP4461Wiper::WIPER0 || pot_index == MCP4461Wiper::WIPER1 ? MCP4461TCONReg::TCON0 : MCP4461TCONReg::TCON1;
        uint8_t TCON_readback = readRegister(tcon_register_index);
        TCON_readback &= pot_index == MCP4461Wiper::WIPER0 || pot_index == MCP4461Wiper::WIPER2 ? 0xF0 : 0x0F;
        uint8_t new_TCON = 0x8; //keep shutdown pin off
        uint8_t TCON_offset = pot_index == MCP4461Wiper::WIPER0 || pot_index == MCP4461Wiper::WIPER2 ? 0 : 4;
        
        new_TCON |= terminalConnectedA << static_cast<uint8_t>(MCP4461TCONTerminal::TERMINAL_A);
        new_TCON |= terminalConnectedB << static_cast<uint8_t>(MCP4461TCONTerminal::TERMINAL_B);
        new_TCON |= terminalConnectedW << static_cast<uint8_t>(MCP4461TCONTerminal::TERMINAL_W);

        new_TCON = new_TCON << TCON_offset || TCON_readback;

        writeRegister(tcon_register_index, new_TCON);
    }

private:
    shared::periph::I2CBus& i2c_bus_;
    uint8_t pot_i2c_address_;
}

} // namespace shared::device::mcp
