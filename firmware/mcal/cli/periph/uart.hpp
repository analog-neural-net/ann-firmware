/// @author Samuel Parent, Hydar Zartash
/// @date 2024-11-21

#pragma once

#include <iostream>

#include "shared/comms/uart/msg.hpp"
#include "shared/periph/uart.hpp"

namespace mcal::cli::periph {

class UartBus : public shared::periph::UartBus {
public:
    UartBus(int bus_number) : bus_number_(bus_number) {}
    virtual ~UartBus() = default;

    virtual void Transmit(const shared::uart::Message& msg) override {
        std::cout << "Uart " << bus_number_ << " - " << msg << "\n";
    };

    virtual void ReceiveBlocking(shared::uart::Message& msg) override {
        std::cout << "Uart " << bus_number_ << " - " << msg << "\n";
    };

protected:
    int bus_number_;
};

}  // namespace mcal::cli::periph
