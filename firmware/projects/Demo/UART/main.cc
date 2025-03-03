#include <iostream>

#include "bindings.hpp"

int main() {
    bindings::Initialize();

    uint8_t tx_data[] = {0xDE, 0xAD, 0xBE, 0xEF};
    uint8_t rx_data[4] = {0};
    shared::uart::Message<shared::uart::MessageType::Transmit> tx_msg(tx_data);
    shared::uart::Message<shared::uart::MessageType::Receive> rx_msg(rx_data);

    while (true) {
        std::cout << tx_msg << std::endl;
        bindings::uart_bus.Transmit(tx_msg);
        bindings::uart_bus.ReceiveBlocking(rx_msg);
        std::cout << rx_msg << std::endl;
        bindings::DelayMS(1000);
    }

    return 0;
}