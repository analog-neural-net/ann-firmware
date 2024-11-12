#include "bindings.h"
#include <math.h>
#include "projects/Demo/Blink/bindings.h"

int main() {
    bindings::Initialize();
    uint32_t dac_value = 0;
    float dac_value_f = 0.0;
    float sin_value = 0.0;
    bool button_xor = false;

    while(true) {
        dac_value_f += 0.1;
        sin_value = 1.6f + 1.6f * sin(dac_value_f);
        bindings::dac.Set(sin_value);
        bindings::DelayMS(10);
    }

    while (true) {
        bool button_state = bindings::button.Read();
        button_xor ^= button_state;
        if (button_state) {
            dac_value += 1024;
            if (dac_value > 4096) {
                dac_value = 0;
            } else if (dac_value == 4096) {
                dac_value = 4095;
            }
            bindings::dac.Set(dac_value);
        }
        bindings::DelayMS(30);
        bindings::indicator.Set(button_state);
    }

    return 0;
}