#pragma once

#include <cstdint>

#include "shared/comms/uart/msg.hpp"
#include "shared/periph/uart.hpp"
#include "stm32f7xx_hal.h"

namespace mcal::stm32f767::periph {

class UartBus : public shared::periph::UartBus {
public:
    explicit UartBus(UART_HandleTypeDef* huart) : huart_(huart) {}

    void Transmit(
        const shared::uart::Message<shared::uart::MessageType::Transmit>& msg)
        override {
        HAL_UART_Transmit(huart_, msg.Data(), msg.DataLength(), HAL_MAX_DELAY);
    }

    void ReceiveBlocking(
        shared::uart::Message<shared::uart::MessageType::Receive>& msg)
        override {
        HAL_UART_Receive(huart_, msg.Data(), msg.DataLength(), HAL_MAX_DELAY);
    }

private:
    UART_HandleTypeDef* huart_;
};

}  // namespace mcal::stm32f767::periph
