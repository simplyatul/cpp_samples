/*
 * run: g++ -std=gnu++17 fibo_memoization.cpp
 * Ref: https://www.youtube.com/watch?v=wFRlUNSMK8s
 * Value of Fibo caulated at compile time
 * Check with g++ -S fibo_memoization.cpp
 */

#include <cstdio>
#include <cstdint>

template <uint64_t N>
constexpr uint64_t fib();

template <uint64_t N>
constexpr uint64_t fib_memo = fib<N>();

template <uint64_t N>
constexpr uint64_t fib() {
    if constexpr (N < 2) return N;
    else return fib_memo<N-1> + fib_memo<N-2>;
}

int main(int argc, char** argv) {
    constexpr uint64_t f = fib<100>();
    printf("%ld\n", f);
    return 0;
}

