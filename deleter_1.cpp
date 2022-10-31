/*
 * run: g++ deleter_1.cpp
 * using smart pointers with dynamic arrays
 */

#include <iostream>
#include <memory>


int main() {
    {
        int *p = new int[6]{0, 1, 2, 3, 4, 5};
        std::cout << p[2] << std::endl;
        delete []p;
    }

    {
        /*
         * It is possible to use smart pointers with 
         * dynamic array, but default delete will 
         * call delete but not delete with subscript
         */
        std::unique_ptr<int> p {new int[6]{0, 1, 2, 3, 4, 5}};
        std::cout << *p << std::endl;
        /*
         * second issue is array elements can not accessed using
         * subscript directly. So p[1] = 10 gives error 
         * bec operator [] is not provided by unique pointer
         * you can access, but sysntax is not simple
         */ 
         p.get()[2] = 22;
         std::cout << p.get()[2] << std::endl;
    }
    {
        /*
         * Solution is to use template specialization for smart pointer
         * with subscript 
         */
         std::unique_ptr<int[]> p {new int[6]{0, 1, 2, 3, 4, 5}};
         std::cout << p[3] << std::endl;
    }
    {
        /*
         * specialization for shared pointer is added from C++ 17 
         */
         std::shared_ptr<int[]> p {new int[6]{0, 1, 2, 3, 4, 5}};
         std::cout << p[4] << std::endl;
    }
    return 0;
}
