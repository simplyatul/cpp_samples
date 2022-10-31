/*
 * run: g++ make_funcions_0.cpp
 * 
 */

#include <iostream>
#include <memory>


int main() {
    {
        std::unique_ptr<int> p(new int{5});
        std::cout << *p << std::endl;

        /*
         * use make_unique w/o calling new
         */
        auto u = std::make_unique<int>(8);
        std::cout << *u << std::endl;
    }
    {
        /*
         * make_unique is variadic type of template
         * so it accepts variable number of args
         */
        class Point {
            public:
                Point(int x, int y) {}
        };

        auto p = std::make_unique<Point>(10, 20);
    }

    {
        int size = 5;
        auto arr = std::make_unique<int[]>(size);
        // You can not initialize dynamic array using make_unique
        arr[0] = 3;
    }
    /* 
     * make_shared works in similar fashion to that of make_unique
     * however, it take care of creating control block as well
     */
    
    /*
     * Disadvantage of make functions 
     * there is no way to declare custom deleter
     * 
     * So if you are not using custom deleter then it is better
     * to use make functions always.
     */
    return 0;
}
