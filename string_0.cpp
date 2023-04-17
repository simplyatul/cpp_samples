#include <iostream>
#include <string>

enum state {ONE=0, TWO, THREE};
const char *ssNames[] = {"ONE", "TWO", "THREE"};

class Test {
private:
    std::string color[4] = { "Blue", "Red",
                              "Orange", "Yellow" };
public:
    void printColor() {
        std::cout << color[ONE] << std::endl;
    }
};

int main() {
    state s = THREE;
    std::cout << "In State: " << ssNames[s] << std::endl;
    std::cout << "In State: " << std::string(ssNames[s]) << std::endl;
    Test t;
    t.printColor();
    return 0;
}
