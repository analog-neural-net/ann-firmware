#include "bindings.h"
#include <math.h>

float sine_value(float x) {
    return 1.6f + 1.6f * sin(x);
}

int main() {
    bindings::Initialize();

    float x = 0.0;

    //superloop
    while (true) {
        x += 0.01f;
        bindings::dac.Set(sine_value(x));
        bindings::DelayMS(10);
    }

    return 0;
}