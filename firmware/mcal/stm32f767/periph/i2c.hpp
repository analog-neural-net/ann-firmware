/// @author Hydar Zartash
/// @date 2025-02-10

#pragma once

#include "shared/comms/i2c/msg.hpp"
#include "shared/periph/i2c.hpp"
#include "stm32f7xx_hal.h"
#include <iostream>

namespace mcal::stm32f767::periph {

class I2CBus : public shared::periph::I2CBus {
public:
    I2CBus(I2C_HandleTypeDef* hi2c) : hi2c_(hi2c) {}

    void Write(const shared::i2c::Message& msg) override {
        auto error = HAL_I2C_Master_Transmit(hi2c_, msg.Address() << 1, msg.Data(),
                                msg.DataLength(), HAL_MAX_DELAY);

        std::cout << "I2C Write Error Code: " << std::to_string((uint8_t)error) << std::endl;
    }

    void Read(shared::i2c::Message& msg) override {
        HAL_I2C_Master_Receive(hi2c_, (msg.Address() << 1) | 0x1, msg.Data(),
                               msg.DataLength(), HAL_MAX_DELAY);
    }

private:
    I2C_HandleTypeDef* hi2c_;
};

}  // namespace mcal::stm32f767::periph