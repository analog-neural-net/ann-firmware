/// @author Samuel Parent, Hydar Zartash
/// @date 2025-02-15

#include <cstdint>

#include "shared/comms/uart/msg.hpp"
#include "shared/util/peripheral.hpp"

#pragma once

namespace shared::periph {

class UartBus : public util::Peripheral {
public:
    virtual void Transmit(const uart::Message& msg) = 0;
    virtual void ReceiveBlocking(uart::Message& msg) = 0;
};

}  // namespace shared::periph

/*
cpmmands:
get individual pot value, x
write individual pot value, x
request inference results x
start inference, _/
get error codes, _/
clear error codes, _/
start calibration,
get calibration results,
start self test routine,
get self test results
*/