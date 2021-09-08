#include "timer.h"

class A {
private:
    Timer t1 = Timer();
    int k;
public:
    friend void callaFn(A* a);
    A();
    void aFn();
};
