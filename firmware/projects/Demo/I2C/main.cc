#include <cstdint>

#include "bindings.hpp"
#include "shared/comms/i2c/msg.hpp"

int main() {
    bindings::Initialize();

    while (true) {
        uint8_t data1[] = {0x02, 0x03, 0x05};
        bindings::indicator.SetHigh();

        bindings::i2c_bus2.Write(
            shared::i2c::Message(0xF, data1, shared::i2c::MessageType::Write));
        bindings::DelayMS(1000);

        uint8_t data2[1];
        auto read_msg =
            shared::i2c::Message(0xF, data2, shared::i2c::MessageType::Read);
        bindings::i2c_bus2.Read(read_msg);
        if(data2[0] == 0xFF) {
            bindings::indicator.SetHigh();
        } else {
            bindings::indicator.SetLow();
        }

        bindings::DelayMS(1000);
    }

    return 0;
}