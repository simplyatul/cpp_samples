/*
 * run: g++ templateMetap_0.cpp
 * Template Metaprogramming
 * Calculates Sum(N) = N + (N-1) + (N-2) + ... + 1
 */

#include <iostream>

template <size_t N>
struct Sum {
    enum {value = N + Sum<N-1>::value};
};

// Specialization for Temincation
template <>
struct Sum<1> {
    enum {value = 1};
};

int main()
{
    Sum<100> a;
    /* at certain number, template instantiation depth exceeds
     * use constexpt as solution which has higher depth
     * refer fibo_memoization.cpp
     */
    std::cout << "Sum: " << a.value << "\n";
    return 0;
}


