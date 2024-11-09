/// @author Hydar Zartash
/// @date 2024-11-06

#pragma once

#include <cstdint>
#include <math.h>
#include "shared/periph/dac.h"
#include "stm32f7xx_hal.h"

namespace mcal::stm32f767::periph {

class DACOutput : public shared::periph::DACOutput {
private:
    DAC_HandleTypeDef* hdac_;
    uint32_t dac_channel_;


public:
    DACOutput(DAC_HandleTypeDef* hdac, uint32_t dac_channel)
        : hdac_(hdac), dac_channel_(dac_channel){}; //constructor

    void Start() override {
        HAL_DAC_Start(hdac_, dac_channel_);
    }

    // @brief Set the value of the DAC
    // @param value The value to set the DAC to
    void Set(float value) override {

        //if dac isn't started, start it
        //TODO: change to error/halt
        HAL_DAC_StateTypeDef dac_state = HAL_DAC_GetState(hdac_);
        if (dac_state != HAL_DAC_STATE_READY) {
            Start();
        }

        //convert float to uint32_t
        uint32_t dac_value = (uint32_t)round(value / 3.3f * 4095.0);

        //set dac value, 12 bits right aligned in the uint32_t register
        HAL_DAC_SetValue(hdac_, dac_channel_, DAC_ALIGN_12B_R, dac_value);
    }

    float Get() override {
        float max_value = 3.3f;
        uint32_t dac_value = HAL_DAC_GetValue(hdac_, dac_channel_);
        return (float)dac_value / 4095.0f * max_value;
    }

    void Stop() override {

        HAL_DAC_StateTypeDef dac_state = HAL_DAC_GetState(hdac_);
        if (dac_state == HAL_DAC_STATE_READY) {
            Start();
        }
        HAL_DAC_Stop(hdac_, dac_channel_);
    }
};

}  // namespace mcal::stm32f767::periph
