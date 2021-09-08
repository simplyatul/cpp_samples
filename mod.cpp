#include <iostream>
#include <cstdint>

#define EXITCODE "EXIT"

int main() {
    uint8_t seqNum=0;
    std::cout << "seqNum: " << static_cast<int>(seqNum) << std::endl;
    std::cout << "seqNum mod 0xFF: " << static_cast<int>((seqNum) % 0xFF) << std::endl;
    std::cout << "seqNum+1 mod 0xFF: " << static_cast<int>((seqNum+1) % 0xFF) << std::endl;
    std::cout << "seqNum w/ ter op: " << static_cast<int>( (0xFF == seqNum? 0: (seqNum+1)) ) << std::endl;

    return 0;
}

