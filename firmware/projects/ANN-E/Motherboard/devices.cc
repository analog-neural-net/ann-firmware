#include <sys/_stdint.h>
#include "bindings.hpp"
#include "devices.hpp"
#include "projects/Demo/DigitalAnalogConverter/bindings.hpp"
#include "shared/device/dac.hpp"
#include "shared/device/digital_pot.hpp"
#include "shared/device/i2c_mux.hpp"
#include "shared/device/mcp/mcp4461.hpp"
#include "shared/device/mcp/mcp4728.hpp"
#include "shared/device/ti/tca9548a.hpp"

constexpr float kVoltageReference = 5.5F;
constexpr uint8_t kMcp4461BaseAddr = 0x2C;

namespace {
using namespace shared::device;

mcp::MCP4728 mcp4728_dac1(bindings::i2c_bus1A, 0x00,
                          kVoltageReference);  // TODO: temp address
mcp::MCP4728 mcp4728_dac2(bindings::i2c_bus1A, 0x01,
                          kVoltageReference);  // TODO: temp address
mcp::MCP4728 mcp4728_dac3(bindings::i2c_bus1A, 0x02,
                          kVoltageReference);  // TODO: temp address

ti::TCA9548A tca9548a_i2c_mux1(bindings::i2c_bus1, 0x70);
ti::TCA9548A tca9548a_i2c_mux2(bindings::i2c_bus2, 0x70);
ti::TCA9548A tca9548a_i2c_mux3(bindings::i2c_bus3, 0x70);

// Layer 0, WNBlock 0

mcp::MCP4461 mcp4461_pot_controller_l0f0(bindings::i2c_bus1D, kMcp4461BaseAddr);
mcp::MCP4461 mcp4461_pot_controller_l0b0(bindings::i2c_bus1D,
                                         kMcp4461BaseAddr + 1);

mcp::MCP4461 mcp4461_pot_controller_l0r0c0(bindings::i2c_bus1A,
                                           kMcp4461BaseAddr + 0);
mcp::MCP4461 mcp4461_pot_controller_l0r0c1(bindings::i2c_bus1B,
                                           kMcp4461BaseAddr + 0);
mcp::MCP4461 mcp4461_pot_controller_l0r0c2(bindings::i2c_bus1C,
                                           kMcp4461BaseAddr + 0);

mcp::MCP4461 mcp4461_pot_controller_l0r1c0(bindings::i2c_bus1A,
                                           kMcp4461BaseAddr + 1);
mcp::MCP4461 mcp4461_pot_controller_l0r1c1(bindings::i2c_bus1B,
                                           kMcp4461BaseAddr + 1);
mcp::MCP4461 mcp4461_pot_controller_l0r1c2(bindings::i2c_bus1C,
                                           kMcp4461BaseAddr + 1);

mcp::MCP4461 mcp4461_pot_controller_l0r2c0(bindings::i2c_bus1A,
                                           kMcp4461BaseAddr + 2);
mcp::MCP4461 mcp4461_pot_controller_l0r2c1(bindings::i2c_bus1B,
                                           kMcp4461BaseAddr + 2);
mcp::MCP4461 mcp4461_pot_controller_l0r2c2(bindings::i2c_bus1C,
                                           kMcp4461BaseAddr + 2);

mcp::MCP4461 mcp4461_pot_controller_l0r3c0(bindings::i2c_bus1A,
                                           kMcp4461BaseAddr + 3);
mcp::MCP4461 mcp4461_pot_controller_l0r3c1(bindings::i2c_bus1B,
                                           kMcp4461BaseAddr + 3);
mcp::MCP4461 mcp4461_pot_controller_l0r3c2(bindings::i2c_bus1C,
                                           kMcp4461BaseAddr + 3);

// Layer 0, WNBlock 1

mcp::MCP4461 mcp4461_pot_controller_l0f1(bindings::i2c_bus2D, kMcp4461BaseAddr);
mcp::MCP4461 mcp4461_pot_controller_l0b1(bindings::i2c_bus2D,
                                         kMcp4461BaseAddr + 1);

mcp::MCP4461 mcp4461_pot_controller_l0r4c0(bindings::i2c_bus2A,
                                           kMcp4461BaseAddr + 0);
mcp::MCP4461 mcp4461_pot_controller_l0r4c1(bindings::i2c_bus2B,
                                           kMcp4461BaseAddr + 0);
mcp::MCP4461 mcp4461_pot_controller_l0r4c2(bindings::i2c_bus2C,
                                           kMcp4461BaseAddr + 0);

mcp::MCP4461 mcp4461_pot_controller_l0r5c0(bindings::i2c_bus2A,
                                           kMcp4461BaseAddr + 1);
mcp::MCP4461 mcp4461_pot_controller_l0r5c1(bindings::i2c_bus2B,
                                           kMcp4461BaseAddr + 1);
mcp::MCP4461 mcp4461_pot_controller_l0r5c2(bindings::i2c_bus2C,
                                           kMcp4461BaseAddr + 1);

mcp::MCP4461 mcp4461_pot_controller_l0r6c0(bindings::i2c_bus2A,
                                           kMcp4461BaseAddr + 2);
mcp::MCP4461 mcp4461_pot_controller_l0r6c1(bindings::i2c_bus2B,
                                           kMcp4461BaseAddr + 2);
mcp::MCP4461 mcp4461_pot_controller_l0r6c2(bindings::i2c_bus2C,
                                           kMcp4461BaseAddr + 2);

mcp::MCP4461 mcp4461_pot_controller_l0r7c0(bindings::i2c_bus2A,
                                           kMcp4461BaseAddr + 3);
mcp::MCP4461 mcp4461_pot_controller_l0r7c1(bindings::i2c_bus2B,
                                           kMcp4461BaseAddr + 3);
mcp::MCP4461 mcp4461_pot_controller_l0r7c2(bindings::i2c_bus2C,
                                           kMcp4461BaseAddr + 3);

// Layer 0, WNBlock 2

mcp::MCP4461 mcp4461_pot_controller_l0f2(bindings::i2c_bus3D, kMcp4461BaseAddr);
mcp::MCP4461 mcp4461_pot_controller_l0b2(bindings::i2c_bus3D,
                                         kMcp4461BaseAddr + 1);

mcp::MCP4461 mcp4461_pot_controller_l0r8c0(bindings::i2c_bus3A,
                                           kMcp4461BaseAddr + 0);
mcp::MCP4461 mcp4461_pot_controller_l0r8c1(bindings::i2c_bus3B,
                                           kMcp4461BaseAddr + 0);
mcp::MCP4461 mcp4461_pot_controller_l0r8c2(bindings::i2c_bus3C,
                                           kMcp4461BaseAddr + 0);

mcp::MCP4461 mcp4461_pot_controller_l0r9c0(bindings::i2c_bus3A,
                                           kMcp4461BaseAddr + 1);
mcp::MCP4461 mcp4461_pot_controller_l0r9c1(bindings::i2c_bus3B,
                                           kMcp4461BaseAddr + 1);
mcp::MCP4461 mcp4461_pot_controller_l0r9c2(bindings::i2c_bus3C,
                                           kMcp4461BaseAddr + 1);

mcp::MCP4461 mcp4461_pot_controller_l0r10c0(bindings::i2c_bus3A,
                                            kMcp4461BaseAddr + 2);
mcp::MCP4461 mcp4461_pot_controller_l0r10c1(bindings::i2c_bus3B,
                                            kMcp4461BaseAddr + 2);
mcp::MCP4461 mcp4461_pot_controller_l0r10c2(bindings::i2c_bus3C,
                                            kMcp4461BaseAddr + 2);

mcp::MCP4461 mcp4461_pot_controller_l0r11c0(bindings::i2c_bus3A,
                                            kMcp4461BaseAddr + 3);
mcp::MCP4461 mcp4461_pot_controller_l0r11c1(bindings::i2c_bus3B,
                                            kMcp4461BaseAddr + 3);
mcp::MCP4461 mcp4461_pot_controller_l0r11c2(bindings::i2c_bus3C,
                                            kMcp4461BaseAddr + 3);

// Layer 1, WNBlock 0

mcp::MCP4461 mcp4461_pot_controller_l1f0(bindings::i2c_bus1H, kMcp4461BaseAddr);
mcp::MCP4461 mcp4461_pot_controller_l1b0(bindings::i2c_bus1H,
                                         kMcp4461BaseAddr + 1);

mcp::MCP4461 mcp4461_pot_controller_l1r0c0(bindings::i2c_bus1E,
                                           kMcp4461BaseAddr + 0);
mcp::MCP4461 mcp4461_pot_controller_l1r0c1(bindings::i2c_bus1F,
                                           kMcp4461BaseAddr + 0);
mcp::MCP4461 mcp4461_pot_controller_l1r0c2(bindings::i2c_bus1G,
                                           kMcp4461BaseAddr + 0);

mcp::MCP4461 mcp4461_pot_controller_l1r1c0(bindings::i2c_bus1E,
                                           kMcp4461BaseAddr + 1);
mcp::MCP4461 mcp4461_pot_controller_l1r1c1(bindings::i2c_bus1F,
                                           kMcp4461BaseAddr + 1);
mcp::MCP4461 mcp4461_pot_controller_l1r1c2(bindings::i2c_bus1G,
                                           kMcp4461BaseAddr + 1);

mcp::MCP4461 mcp4461_pot_controller_l1r2c0(bindings::i2c_bus1E,
                                           kMcp4461BaseAddr + 2);
mcp::MCP4461 mcp4461_pot_controller_l1r2c1(bindings::i2c_bus1F,
                                           kMcp4461BaseAddr + 2);
mcp::MCP4461 mcp4461_pot_controller_l1r2c2(bindings::i2c_bus1G,
                                           kMcp4461BaseAddr + 2);

mcp::MCP4461 mcp4461_pot_controller_l1r3c0(bindings::i2c_bus1E,
                                           kMcp4461BaseAddr + 3);
mcp::MCP4461 mcp4461_pot_controller_l1r3c1(bindings::i2c_bus1F,
                                           kMcp4461BaseAddr + 3);
mcp::MCP4461 mcp4461_pot_controller_l1r3c2(bindings::i2c_bus1G,
                                           kMcp4461BaseAddr + 3);

// Layer 1, WNBlock 1

mcp::MCP4461 mcp4461_pot_controller_l1f1(bindings::i2c_bus2H, kMcp4461BaseAddr);
mcp::MCP4461 mcp4461_pot_controller_l1b1(bindings::i2c_bus2H,
                                         kMcp4461BaseAddr + 1);

mcp::MCP4461 mcp4461_pot_controller_l1r4c0(bindings::i2c_bus2E,
                                           kMcp4461BaseAddr + 0);
mcp::MCP4461 mcp4461_pot_controller_l1r4c1(bindings::i2c_bus2F,
                                           kMcp4461BaseAddr + 0);
mcp::MCP4461 mcp4461_pot_controller_l1r4c2(bindings::i2c_bus2G,
                                           kMcp4461BaseAddr + 0);

mcp::MCP4461 mcp4461_pot_controller_l1r5c0(bindings::i2c_bus2E,
                                           kMcp4461BaseAddr + 1);
mcp::MCP4461 mcp4461_pot_controller_l1r5c1(bindings::i2c_bus2F,
                                           kMcp4461BaseAddr + 1);
mcp::MCP4461 mcp4461_pot_controller_l1r5c2(bindings::i2c_bus2G,
                                           kMcp4461BaseAddr + 1);

mcp::MCP4461 mcp4461_pot_controller_l1r6c0(bindings::i2c_bus2E,
                                           kMcp4461BaseAddr + 2);
mcp::MCP4461 mcp4461_pot_controller_l1r6c1(bindings::i2c_bus2F,
                                           kMcp4461BaseAddr + 2);
mcp::MCP4461 mcp4461_pot_controller_l1r6c2(bindings::i2c_bus2G,
                                           kMcp4461BaseAddr + 2);

mcp::MCP4461 mcp4461_pot_controller_l1r7c0(bindings::i2c_bus2E,
                                           kMcp4461BaseAddr + 3);
mcp::MCP4461 mcp4461_pot_controller_l1r7c1(bindings::i2c_bus2F,
                                           kMcp4461BaseAddr + 3);
mcp::MCP4461 mcp4461_pot_controller_l1r7c2(bindings::i2c_bus2G,
                                           kMcp4461BaseAddr + 3);

// Layer 1, WNBlock 2

mcp::MCP4461 mcp4461_pot_controller_l1f2(bindings::i2c_bus3H, kMcp4461BaseAddr);
mcp::MCP4461 mcp4461_pot_controller_l1b2(bindings::i2c_bus3H,
                                         kMcp4461BaseAddr + 1);

mcp::MCP4461 mcp4461_pot_controller_l1r8c0(bindings::i2c_bus3E,
                                           kMcp4461BaseAddr + 0);
mcp::MCP4461 mcp4461_pot_controller_l1r8c1(bindings::i2c_bus3F,
                                           kMcp4461BaseAddr + 0);
mcp::MCP4461 mcp4461_pot_controller_l1r8c2(bindings::i2c_bus3G,
                                           kMcp4461BaseAddr + 0);

mcp::MCP4461 mcp4461_pot_controller_l1r9c0(bindings::i2c_bus3E,
                                           kMcp4461BaseAddr + 1);
mcp::MCP4461 mcp4461_pot_controller_l1r9c1(bindings::i2c_bus3F,
                                           kMcp4461BaseAddr + 1);
mcp::MCP4461 mcp4461_pot_controller_l1r9c2(bindings::i2c_bus3G,
                                           kMcp4461BaseAddr + 1);

mcp::MCP4461 mcp4461_pot_controller_l1r10c0(bindings::i2c_bus3E,
                                            kMcp4461BaseAddr + 2);
mcp::MCP4461 mcp4461_pot_controller_l1r10c1(bindings::i2c_bus3F,
                                            kMcp4461BaseAddr + 2);
mcp::MCP4461 mcp4461_pot_controller_l1r10c2(bindings::i2c_bus3G,
                                            kMcp4461BaseAddr + 2);

mcp::MCP4461 mcp4461_pot_controller_l1r11c0(bindings::i2c_bus3E,
                                            kMcp4461BaseAddr + 3);
mcp::MCP4461 mcp4461_pot_controller_l1r11c1(bindings::i2c_bus3F,
                                            kMcp4461BaseAddr + 3);
mcp::MCP4461 mcp4461_pot_controller_l1r11c2(bindings::i2c_bus3G,
                                            kMcp4461BaseAddr + 3);

}  // namespace

namespace device {

shared::device::DigitalAnalogConverter<kNumOutputsPerDac>& dac1 = mcp4728_dac1;
shared::device::DigitalAnalogConverter<kNumOutputsPerDac>& dac2 = mcp4728_dac2;
shared::device::DigitalAnalogConverter<kNumOutputsPerDac>& dac3 = mcp4728_dac3;
shared::device::DigitalAnalogConverter<kNumOutputsPerDac>* dacs[] = {
    &dac1, &dac2, &dac3};

shared::device::DigitalAnalogConverterGroup<kNumExternalDacs, kNumOutputsPerDac>
    dac_group(dacs);

shared::device::I2CMultiplexer<ti::TCA9548AChannel>& i2c_mux1 =
    tca9548a_i2c_mux1;
shared::device::I2CMultiplexer<ti::TCA9548AChannel>& i2c_mux2 =
    tca9548a_i2c_mux2;
shared::device::I2CMultiplexer<ti::TCA9548AChannel>& i2c_mux3 =
    tca9548a_i2c_mux3;


shared::device::DigitalPotentiometer<uint8_t> mcp4461_pot_controller_l0


}  // namespace device