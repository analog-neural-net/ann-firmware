#include "bindings.h"
#include <math.h>
#include <string.h>

float sine_value(float x) {
    return 1.6f + 1.6f * sin(x);
}

int main() {
    bindings::Initialize();

    uint8_t message[] = {0x01, 0x02, 0x03, 0x04};
    bool indicator_state = false;

    //superloop
    while (true) {
        bindings::i2c.Write(0x2E, message, sizeof(message));
        indicator_state = !indicator_state;
        bindings::indicator.Set(indicator_state);
        bindings::DelayMS(1000);
        message[0]++;
        message[1]++;
        message[2]++;
        message[3]++;
    }

    return 0;
}