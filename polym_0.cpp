/*
 * run: g++ polym_0.cpp
 */

#include <iostream>
#include "common.h"

class A {
    public:
        virtual void mustImplement() = 0;
        virtual void onlyInB() { };

        virtual void onlyInA() {
            std::cout << "onlyInA" << std::endl;
        }

        virtual void print_me(void) {
            std::cout << "I'm A" << std::endl;
        }

        virtual ~A() {
            std::cout << "D'tor A" << std::endl;
        }
};

class B : public A {
    public:
        void onlyInB() {
            std::cout << "onlyInB" << std::endl;
        }
        virtual void print_me(void) {
            std::cout << "I'm B" << std::endl;
        }
        virtual void mustImplement() {}
        virtual ~B() {
            std::cout << "D'tor B" << std::endl;
        }
};

class C : public A {
    public:
        virtual ~C() {
            std::cout << "D'tor C" << std::endl;
        }
        virtual void mustImplement() {}
};

int main() {

    /*
    A a;
    A* p = &a;
    p->print_me();
    */

    A* p = nullptr;

    std::cout << "--------------------" << std::endl;
    std::cout << "pointing to object B" << std::endl;
    std::cout << "--------------------" << std::endl;
    p = new B;
    p->print_me();
    p->onlyInB();
    p->onlyInA();
    delete p;
    
    std::cout << "--------------------" << std::endl;
    std::cout << "pointing to object C" << std::endl;
    std::cout << "--------------------" << std::endl;
    p = new C;
    p->print_me();
    p->onlyInA();
    
    return 0;
}
