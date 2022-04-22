/*
 * run: g++ fibo_simple.cpp
 */

#include <cstdio>

int fib(int n) {
    if (n < 2) return n;
    return fib(n-1) + fib(n-2);
}

int main() {
    int n = 4;
    int f = fib(n);
    printf("%d %d\n", n, f);
    return 0;
}

