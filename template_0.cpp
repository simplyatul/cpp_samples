/*
 * run: g++ template_0.cpp
 */


#include <iostream>
#include <stdio.h>

template<typename T, typename X>
void add(T t, X x) {
    puts(__PRETTY_FUNCTION__);
    puts(std::to_string(sizeof(T)).c_str());
    puts(std::to_string(sizeof(X)).c_str());
}

int main()
{
    add(2,2);           // T = int; X = int
    add(2,2.0);         // T = int; X = double
    add('x', 3);        // T = char; X = int
    add('x', 5u);       // T = char; X = unsigned int
    add(4ULL, 5l);      // T = long long unsigned int; X = long int
    add(4ull, 5L);      // T = long long unsigned int; X = long int
    add(4.0f, 5l);      // T = float; X = long int
    add((short)(2), 5L); // T = short int; X = long int
    add((unsigned short)(2), 5L); // T = short unsigned int; X = long int
    add(size_t(2), 3); // T = long unsigned int; X = int
    return 0;
}


