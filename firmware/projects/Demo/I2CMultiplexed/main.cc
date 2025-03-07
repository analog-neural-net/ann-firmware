#include <cstdint>
#include <iostream>

#include "bindings.hpp"
#include "shared/comms/i2c/msg.hpp"

int main() {
    bindings::Initialize();

    uint8_t data1[] = {0xDE, 0xAD, 0xBE, 0xEF, 0x00};
    uint8_t data2[] = {0xAA, 0xBB, 0xCC, 0xDD, 0x00};

    while (true) {

        if (button_state) {
            auto write_msg = shared::i2c::Message(
                0x2C, data1, shared::i2c::MessageType::Write);

            std::cout << write_msg << std::endl;

            bindings::i2c_bus1A.Write(write_msg);
            data1[4] += 0x01;
        } else {
            auto write_msg = shared::i2c::Message(
                0x2C, data2, shared::i2c::MessageType::Write);

            std::cout << write_msg << std::endl;

            bindings::i2c_bus1B.Write(write_msg);
            data2[4] += 0x01;
        }

        bindings::DelayMS(1000);
    }

    return 0;
}
