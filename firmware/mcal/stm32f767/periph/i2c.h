/// @author Hydar Zartash
/// @date 2024-11-09

#pragma once

#include "shared/periph/i2c.h"
#include "stm32f7xx_hal.h"

namespace mcal::stm32f767::periph {

class I2C : public shared::periph::I2C {
private:
    I2C_HandleTypeDef* hi2c_;

public:
    I2C(I2C_HandleTypeDef* hi2c) : hi2c_(hi2c) {}

    void Write(uint8_t address, uint8_t* data, uint8_t length) override {
        HAL_I2C_Master_Transmit(hi2c_, (uint8_t)(address<<1), data, length, HAL_MAX_DELAY);
    }

    void Read(uint8_t address, uint8_t* data, uint8_t length) override {
        HAL_I2C_Master_Receive(hi2c_, (uint8_t)(address<<1), data, length, HAL_MAX_DELAY);
    }  
};

}  // namespace mcal::stm32f767::periph

