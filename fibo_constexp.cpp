/*
 * run: g++ fibo_constexp.cpp
 * Value of Fibo caulated at compile time
 * Check g++ -S fibo_constexp.cpp 
 */

#include <cstdio>

constexpr int fib(int n) {
    if (n < 2) return n;
    return fib(n-1) + fib(n-2);
}

int main() {
    constexpr int n = 40;
    /*
     * as you increase n, compilation will take more time
     * at some point, it will throw the error
     * error: ‘constexpr’ evaluation operation count exceeds limit of 33554432 (use -fconstexpr-ops-limit= to increase the limit)
     * Solution - use memoization. Refer fibo_memoization.cpp
     */
    constexpr int f = fib(n);
    printf("%d %d\n", n, f);
    return 0;
}

