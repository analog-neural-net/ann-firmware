#pragma once

#include "inc/network_params.hpp"
#include "shared/device/dac.hpp"
#include "shared/device/digital_pot.hpp"
#include "shared/device/i2c_mux.hpp"
#include "shared/device/ti/tca9548a.hpp"

namespace device {

constexpr size_t kNumExternalDacs = 3;
constexpr size_t kNumOutputsPerDac = 4;

extern shared::device::DigitalAnalogConverterGroup<
    kNumExternalDacs, kNumOutputsPerDac> dac_group;

extern shared::device::I2CMultiplexer<shared::device::ti::TCA9548AChannel>&
    i2c_mux1;
extern shared::device::I2CMultiplexer<shared::device::ti::TCA9548AChannel>&
    i2c_mux2;
extern shared::device::I2CMultiplexer<shared::device::ti::TCA9548AChannel>&
    i2c_mux3;

extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n0f;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n0b;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n0w0;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n0w1;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n0w2;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n0w3;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n0w4;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n0w5;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n0w6;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n0w7;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n0w8;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n0w9;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n0w10;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n0w11;

extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n1f;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n1b;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n1w0;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n1w1;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n1w2;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n1w3;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n1w4;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n1w5;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n1w6;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n1w7;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n1w8;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n1w9;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n1w10;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n1w11;

extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n2f;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n2b;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n2w0;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n2w1;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n2w2;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n2w3;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n2w4;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n2w5;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n2w6;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n2w7;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n2w8;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n2w9;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n2w10;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n2w11;

extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n3f;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n3b;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n3w0;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n3w1;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n3w2;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n3w3;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n3w4;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n3w5;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n3w6;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n3w7;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n3w8;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n3w9;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n3w10;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n3w11;

extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n4f;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n4b;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n4w0;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n4w1;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n4w2;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n4w3;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n4w4;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n4w5;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n4w6;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n4w7;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n4w8;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n4w9;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n4w10;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n4w11;

extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n5f;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n5b;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n5w0;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n5w1;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n5w2;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n5w3;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n5w4;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n5w5;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n5w6;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n5w7;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n5w8;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n5w9;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n5w10;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n5w11;

extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n6f;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n6b;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n6w0;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n6w1;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n6w2;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n6w3;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n6w4;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n6w5;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n6w6;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n6w7;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n6w8;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n6w9;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n6w10;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n6w11;

extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n7f;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n7b;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n7w0;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n7w1;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n7w2;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n7w3;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n7w4;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n7w5;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n7w6;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n7w7;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n7w8;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n7w9;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n7w10;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n7w11;

extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n8f;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n8b;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n8w0;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n8w1;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n8w2;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n8w3;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n8w4;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n8w5;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n8w6;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n8w7;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n8w8;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n8w9;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n8w10;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n8w11;

extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n9f;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n9b;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n9w0;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n9w1;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n9w2;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n9w3;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n9w4;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n9w5;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n9w6;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n9w7;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n9w8;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n9w9;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n9w10;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n9w11;

extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n10f;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n10b;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n10w0;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n10w1;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n10w2;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n10w3;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n10w4;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n10w5;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n10w6;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n10w7;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n10w8;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n10w9;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n10w10;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n10w11;

extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n11f;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n11b;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n11w0;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n11w1;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n11w2;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n11w3;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n11w4;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n11w5;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n11w6;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n11w7;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n11w8;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n11w9;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n11w10;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l0n11w11;

extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n0f;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n0b;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n0w0;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n0w1;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n0w2;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n0w3;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n0w4;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n0w5;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n0w6;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n0w7;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n0w8;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n0w9;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n0w10;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n0w11;

extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n1f;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n1b;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n1w0;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n1w1;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n1w2;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n1w3;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n1w4;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n1w5;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n1w6;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n1w7;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n1w8;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n1w9;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n1w10;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n1w11;

extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n2f;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n2b;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n2w0;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n2w1;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n2w2;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n2w3;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n2w4;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n2w5;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n2w6;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n2w7;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n2w8;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n2w9;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n2w10;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n2w11;

extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n3f;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n3b;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n3w0;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n3w1;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n3w2;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n3w3;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n3w4;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n3w5;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n3w6;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n3w7;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n3w8;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n3w9;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n3w10;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n3w11;

extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n4f;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n4b;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n4w0;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n4w1;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n4w2;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n4w3;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n4w4;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n4w5;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n4w6;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n4w7;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n4w8;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n4w9;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n4w10;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n4w11;

extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n5f;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n5b;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n5w0;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n5w1;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n5w2;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n5w3;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n5w4;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n5w5;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n5w6;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n5w7;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n5w8;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n5w9;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n5w10;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n5w11;

extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n6f;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n6b;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n6w0;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n6w1;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n6w2;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n6w3;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n6w4;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n6w5;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n6w6;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n6w7;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n6w8;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n6w9;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n6w10;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n6w11;

extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n7f;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n7b;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n7w0;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n7w1;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n7w2;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n7w3;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n7w4;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n7w5;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n7w6;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n7w7;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n7w8;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n7w9;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n7w10;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n7w11;

extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n8f;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n8b;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n8w0;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n8w1;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n8w2;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n8w3;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n8w4;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n8w5;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n8w6;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n8w7;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n8w8;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n8w9;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n8w10;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n8w11;

extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n9f;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n9b;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n9w0;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n9w1;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n9w2;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n9w3;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n9w4;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n9w5;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n9w6;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n9w7;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n9w8;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n9w9;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n9w10;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n9w11;

extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n10f;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n10b;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n10w0;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n10w1;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n10w2;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n10w3;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n10w4;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n10w5;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n10w6;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n10w7;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n10w8;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n10w9;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n10w10;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n10w11;

extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n11f;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n11b;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n11w0;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n11w1;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n11w2;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n11w3;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n11w4;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n11w5;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n11w6;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n11w7;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n11w8;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n11w9;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n11w10;
extern shared::device::DigitalPotentiometer<uint8_t>& pot_l1n11w11;

}  // namespace device