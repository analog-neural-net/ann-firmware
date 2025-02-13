#include <cstring>
#include <iostream>

#include "bindings.hpp"

int main() {
    bindings::Initialize();

    std::string buf;
    std::cout << "Hello World! " << std::endl;

    while (true) {
        std::cout << "Enter text:" << std::endl;
        std::cin >> buf;
        std::cout << "Received: " << buf << std::endl;
        bindings::DelayMs(500);
    }

    return 0;
}