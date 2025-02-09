#pragma once


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

class MCP4461 : public DigitalPotentiometerController<MCP4461Wiper, uint8_t> {
public:

    void SetPosition(MCP4461Wiper pot_index, uint8_t position) override {
        uint8_t transmission[2];
        transmission[0] = (static_cast<uint8_t>(pot_index) << 4) | (static_cast<uint8_t>(MCP4461Command::WRITE_REGISTER) << 2); 
        transmission[1] = position;
        
        i2c::Message msg = i2c::Message(pot_i2c_address_, transmission, i2c::MessageType::Write);
        i2c_bus_.Write(msg);
    }

    uint8_t GetPosition(MCP4461Wiper pot_index) override {
        uint8_t transmission_request = (static_cast<uint8_t>(pot_index) << 4) | (static_cast<uint8_t>(MCP4461Command::READ_REGISTER) << 2);
        uint8_t read_data[2];

        i2c::Message request = i2c::Message(pot_i2c_address_, transmission_request, i2c::MessageType::Write);
        i2c::Message readback = i2c::Message(pot_i2c_address_, read_data, i2c::MessageType::Read);

        i2c_bus_.Write(request);
        i2c_bus_.Read(readback);

    }

    /**
     * @brief Retrieves the terminal connection status for a specified wiper.
     *
     * This function reads the terminal connection (TCON) register for the given wiper index
     * and terminal, and returns the connection status.
     * TCON0[7:0] = Wiper 1[3:0], Wiper0[3:0]
     * TCON1[7:0] = Wiper 3[3:0], Wiper2[3:0]
     * each TCON[3:0] = [1b' shutdown, 1b' terminal A, 1b' terminal W, 1b' terminal B]
     *
     * @param pot_index The wiper index (MCP4461Wiper::WIPER0, MCP4461Wiper::WIPER1, MCP4461Wiper::WIPER2, or MCP4461Wiper::WIPER3).
     * @param terminal The terminal to check (Terminal::A, Terminal::W, or Terminal::B).
     * @return True if the terminal is connected, false otherwise.
     */
    bool GetTerminalConnection(MCP4461Wiper pot_index, Terminal terminal) override {
        //get corresponding TCOn Register
        //TCON0[7:0] = Wiper 1[3:0], Wiper0[3:0]
        //TCON1[7:0] = Wiper 3[3:0], Wiper2[3:0]
        //each TCON[3:0] = [1b' shutdown, 1b' terminal A, 1b' terminal W, 1b' terminal B]
        MCP4461TCONReg tcon_register_index = pot_index == MCP4461Wiper::WIPER0 || pot_index == MCP4461Wiper::WIPER1 ? MCP4461TCONReg::TCON0 : MCP4461TCONReg::TCON1;
        uint8_t transmission_request = (static_cast<uint8_t>(tcon_register_index) << 4) | (static_cast<uint8_t>(MCP4461Command::READ_REGISTER) << 2);
        uint8_t read_data[2];

        i2c::Message request = i2c::Message(pot_i2c_address_, transmission_request, i2c::MessageType::Write);
        i2c::Message readback = i2c::Message(pot_i2c_address_, read_data, i2c::MessageType::Read);

        i2c_bus_.Write(request);
        i2c_bus_.Read(readback);
    }   

    void SetTerminalConnections(MCP4461Wiper pot_index, bool terminalConnectedA, bool terminalConnectedB, bool terminalConnectedW) override {
        MCP4461TCONReg tcon_register_index = pot_index == MCP4461Wiper::WIPER0 || pot_index == MCP4461Wiper::WIPER1 ? MCP4461TCONReg::TCON0 : MCP4461TCONReg::TCON1;
        
        uint8_t TCON_register = 0b1000 | (terminalConnectedA << 2) | (terminalConnectedW << 1) | terminalConnectedB;

        uint8_t transmission[2];

        transmission[0] = (static_cast<uint8_t>(tcon_register_index) << 4) | (static_cast<uint8_t>(MCP4461Command::WRITE_REGISTER) << 2); 
        transmission[1] = position;

    }

private:

    shared::periph::I2CBus& i2c_bus_;
    uint8_t pot_i2c_address_;

    template <typename Mcp4461Register>
    requires(std::is_same_v<Mcp4461Register, MCP4461TCONReg> || std::is_same_v<Mcp4461Register, MCP4461Wiper>)
    void writeRegister(Mcp4461Register reg, uint8_t data) {
        i2c::Message msg;
        uint8_t transmission[2];
        transmission[0] = (static_cast<uint8_t>(reg) << 4) | (static_cast<uint8_t>(MCP4461Command::WRITE_REGISTER) << 2);
        
        transmission[1] = data;

        msg = i2c::Message(pot_i2c_address_, transmission, i2c::MessageType::Write);
        i2c_bus_.Write(msg);
    }

    uint8_t readRegister(Mcp4461Register reg) {
        
        uint8_t transmission_request = (static_cast<uint8_t>(reg) << 4) | (static_cast<uint8_t>(MCP4461Command::READ_REGISTER) << 2);
        uint8_t read_data[2];

        i2c::Message request = i2c::Message(pot_i2c_address_, transmission_request, i2c::MessageType::Write);
        i2c::Message readback = i2c::Message(pot_i2c_address_, read_data, i2c::MessageType::Read);

        i2c_bus_.Write(request);
        i2c_bus_.Read(readback);

        return read_data[1]; //the MSB is empty/unused in this case

    }


    uint8_t readRegister(MCP4461Wiper wiper) {
        i2c::Message msg;
        msg.tx_buf = {static_cast<uint8_t>(wiper)};
        msg.rx_buf = {0};
        i2c_bus_.Transfer(msg);
        return msg.rx_buf[0];
    }


}

} // namespace shared::device::mcp
