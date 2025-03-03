/// @author Samuel Parent, Hydar Zartash
/// @date 2025-02-15

#include <cstdint>

#include "shared/comms/uart/msg.hpp"
#include "shared/util/peripheral.hpp"

#pragma once

namespace shared::periph {

class UartBus : public util::Peripheral {
public:
    virtual void Transmit(
        const uart::Message<uart::MessageType::Transmit>& msg) = 0;
    virtual void ReceiveBlocking(
        uart::Message<uart::MessageType::Receive>& msg) = 0;
};

}  // namespace shared::periph
