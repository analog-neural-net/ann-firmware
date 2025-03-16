#pragma once

#include "shared/device/current_sensor.hpp"
#include "shared/periph/analog_input.hpp"



namespace shared::device::ace {
    
    class MCA1101_5_3 : public shared::device::CurrentSensor {
    public:
        MCA1101_5_3(shared::periph::AnalogInput& reference_current, shared::periph::AnalogInput& output_current) 
        : reference_current_(reference_current), output_current_(output_current) {}

        //Vout = Vref + I_In * GAIN
        // (Vout - Vref) / GAIN = I_in
        float ReadCurrent() override {
            float reference_voltage = reference_current_.ReadVoltage();
            float output_voltage = output_current_.ReadVoltage();
            
            return ( output_voltage - reference_voltage ) / GAIN;
        }

    private:
        //transconductance gain V/A
        constexpr static float GAIN = 0.23f;
        
        periph::AnalogInput& reference_current_;
        periph::AnalogInput& output_current_;

    };

}

