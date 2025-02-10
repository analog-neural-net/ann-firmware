/// @author Hydar Zartash
/// @date 2025-02-10

#pragma once

#include "stm32f7xx_hal.h"
#include "shared/periph/i2c.hpp"
#include "shared/comms/i2c/msg.hpp"

namespace mcal::stm32f767::periph {
    
class I2C : public shared::periph::I2CBus {
private:
    I2C_HandleTypeDef* hi2c_;


public:
    I2C(I2C_HandleTypeDef* hi2c) : hi2c_(hi2c) {}

    void Write(const shared::i2c::Message& msg) override {
        HAL_I2C_Master_Transmit(hi2c_, msg.Address() << 1, msg.Data(), msg.DataLength(), HAL_MAX_DELAY);
    }

    void Read(shared::i2c::Message& msg) override {
        HAL_I2C_Master_Receive(hi2c_, (msg.Address() << 1) | 0x1, msg.Data(), msg.DataLength(), HAL_MAX_DELAY);
    }


};

}  // namespace mcal::stm32f767::periph