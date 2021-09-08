#include "timer.h"
#include "A.h"
#include <thread>
#include <chrono>
#include <atomic>
#include <condition_variable>
#include <mutex>
#include <iostream>

#define LOGTIME \
    std::cout << std::time(nullptr) << ": " << __FUNCTION__ << ":" << __LINE__ << std::endl

void callaFn(A* a) {
    LOGTIME;
    a->k = 5;
    a->aFn();
}

A::A() {
    LOGTIME;
    t1.once(std::chrono::seconds(1), callaFn, this); // Working
}

void A::aFn() {
    LOGTIME;
}


int main() {

    //Timer t = Timer();
    Timer t;
    LOGTIME;
    A a;
    //A *aptr = new A();
    //t.once(std::chrono::seconds(1), callaFn, &a); // Working
    //t.once(std::chrono::seconds(1), callaFn, aptr); // Working

    std::this_thread::sleep_for(std::chrono::seconds(3));
    LOGTIME;
    t.kill();

    return 0;
}
