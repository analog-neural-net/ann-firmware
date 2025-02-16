#pragma once

#include "../bindings.hpp"
#include "shared/device/digital_pot.hpp"
#include "shared/device/mcp/mcp4461.hpp"

namespace device {
using namespace shared::device;
mcp::MCP4461 block_0_pot_00(bindings::I2CBus1A, 0x2C);
mcp::MCP4461(bindings::I2CBus1B, 0x2C);
mcp::MCP4461(bindings::I2CBus1C, 0x2C);
mcp::MCP4461(bindings::I2CBus1D, 0x2C);

mcp::MCP4461(bindings::I2CBus1A, 0x2D);
mcp::MCP4461(bindings::I2CBus1B, 0x2D);
mcp::MCP4461(bindings::I2CBus1C, 0x2D);
mcp::MCP4461(bindings::I2CBus1D, 0x2D);

mcp::MCP4461(bindings::I2CBus1A, 0x2E);
mcp::MCP4461(bindings::I2CBus1B, 0x2E);
mcp::MCP4461(bindings::I2CBus1C, 0x2E);
mcp::MCP4461(bindings::I2CBus1D, 0x2E);

mcp::MCP4461(bindings::I2CBus1A, 0x2F);
mcp::MCP4461(bindings::I2CBus1B, 0x2F);
mcp::MCP4461(bindings::I2CBus1C, 0x2F);
mcp::MCP4461(bindings::I2CBus1D, 0x2F);

};  // namespace device