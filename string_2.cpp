#include <iostream>
#include <cstdint>

#define EXITCODE "EXIT"

int main() {
    std::string pf = "FN_1";
    pf = pf + ":" + std::to_string(__LINE__);
    std::cout << "pf = " << pf << std::endl;
    printf("size of string literal EXIT %ld\n", sizeof(EXITCODE));
    bool val = false;
    std::string s = std::to_string(val);
    std::cout << "s = " << s << std::endl;

    return 0;
}

