/*
 * run: g++ string_1.cpp
 */
#include <iostream>
#include <string>
#include <iostream>     // std::cout
#include <sstream>
#include <iomanip>

int main() {
    uint8_t byteArr[] = {0x21, 0x0e, 0x80};
    std::stringstream ss;
    for(uint32_t i=0; i<sizeof(byteArr); i++) {
        ss << "0x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byteArr[i]) << " ";
    }

    std::cout << "Final String: " << ss.str() << std::endl;
    return 0;
}
