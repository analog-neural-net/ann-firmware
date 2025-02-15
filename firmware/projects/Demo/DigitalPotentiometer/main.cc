#include <stdint.h>

#include <iostream>

#include "bindings.hpp"
#include "devices.hpp"
#include "projects/Demo/DigitalPotentiometer/bindings.hpp"
#include "projects/Demo/DigitalPotentiometer/devices.hpp"
#include "shared/device/digital_pot.hpp"

int main() {
    bindings::Init();

    // Start both pots at midpoint (127)
    uint8_t pot0_position = 127;
    uint8_t pot1_position = 127;
    uint8_t pot2_position = 127;
    uint8_t pot3_position = 127;

    device::digital_pot0.SetPosition(pot0_position);
    device::digital_pot1.SetPosition(pot1_position);
    device::digital_pot2.SetPosition(pot2_position);
    device::digital_pot3.SetPosition(pot3_position);

    pot0_position = device::digital_pot0.GetPosition();
    pot1_position = device::digital_pot1.GetPosition();
    pot2_position = device::digital_pot2.GetPosition();
    pot3_position = device::digital_pot3.GetPosition();

    std::cout << "Pot0 position: " << static_cast<int>(pot0_position)
              << std::endl;
    std::cout << "Pot1 position: " << static_cast<int>(pot1_position)
              << std::endl;
    std::cout << "Pot2 position: " << static_cast<int>(pot2_position)
              << std::endl;
    std::cout << "Pot3 position: " << static_cast<int>(pot3_position)
              << std::endl;

    device::digital_pot0.SetTerminalConnections(true, true, true);
    std::cout << " Pot0 Tcon A: "
              << device::digital_pot0.GetTerminalConnection(
                     shared::device::DigitalPotTerminal::A)
              << " Pot0 Tcon W: "
              << device::digital_pot0.GetTerminalConnection(
                     shared::device::DigitalPotTerminal::W)
              << " Pot0 Tcon B: "
              << device::digital_pot0.GetTerminalConnection(
                     shared::device::DigitalPotTerminal::B)
              << std::endl;

    device::digital_pot1.SetTerminalConnections(true, true, true);
    std::cout << " Pot1 Tcon A: "
              << device::digital_pot1.GetTerminalConnection(
                     shared::device::DigitalPotTerminal::A)
              << " Pot1 Tcon W: "
              << device::digital_pot1.GetTerminalConnection(
                     shared::device::DigitalPotTerminal::W)
              << " Pot1 Tcon B: "
              << device::digital_pot1.GetTerminalConnection(
                     shared::device::DigitalPotTerminal::B)
              << std::endl;

    device::digital_pot2.SetTerminalConnections(true, true, true);
    std::cout << " Pot2 Tcon A: "
              << device::digital_pot2.GetTerminalConnection(
                     shared::device::DigitalPotTerminal::A)
              << " Pot2 Tcon W: "
              << device::digital_pot2.GetTerminalConnection(
                     shared::device::DigitalPotTerminal::W)
              << " Pot2 Tcon B: "
              << device::digital_pot2.GetTerminalConnection(
                     shared::device::DigitalPotTerminal::B)
              << std::endl;

    device::digital_pot3.SetTerminalConnections(true, true, true);
    std::cout << " Pot3 Tcon A: "
              << device::digital_pot3.GetTerminalConnection(
                     shared::device::DigitalPotTerminal::A)
              << " Pot3 Tcon W: "
              << device::digital_pot3.GetTerminalConnection(
                     shared::device::DigitalPotTerminal::W)
              << " Pot3 Tcon B: "
              << device::digital_pot3.GetTerminalConnection(
                     shared::device::DigitalPotTerminal::B)
              << std::endl;

    bindings::red_led.Set(true);

    while (1) {
        bindings::green_led.Set(true);
        bindings::DelayMs(500);
        bindings::green_led.Set(false);
        bindings::DelayMs(500);
    }

    return 0;
}