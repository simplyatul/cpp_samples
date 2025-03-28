/*
 * run: g++ fibo_simple.cpp
 * Value of Fibo calculated at runtime
 */

#include <cstdio>
#include <vector>
#include <unistd.h>
#include "common.h"

using namespace std;

int fibo_Three(int n) {
    int prev1 = 1; // fib(0)
    int prev2 = 0; // fib(1)

    if (n == 0) 
        return prev2;

    if (n == 1) 
        return prev1;

    int curr = 0;
    for(int i=2; i<=n; ++i) {
        curr = prev1 + prev2;
        prev2 = prev1;
        prev1 = curr;
    }
    return curr;
}

int fibo_Two(int n, vector<int>& dp) {

    if(dp[n] != -1)
        return dp[n];
    dp[n] = fibo_Two(n-1, dp) + fibo_Two(n-2, dp);
    return dp[n];
}


int fibo_One(int n) {
    if (n < 2) return n;
    return fibo_One(n-1) + fibo_One(n-2);
}

int main() {
    int n = 20;
    {
        START_TIME(s);
        auto f = fibo_One(n); // Takes ~6 sec if n = 45
        STOP_TIME(e);
        printf("1 Fibo of %d is %d. It tool: %f ms\n", n, f, DIFF_IN_MS(s, e));
    }

    {
        vector<int> dp(n+1, -1);
        dp[0] = 0;
        dp[1] = 1;
        START_TIME(s);
        auto f = fibo_Two(n, dp);
        STOP_TIME(e);
        printf("2 Fibo of %d is %d. It tool: %f ms\n", n, f, DIFF_IN_MS(s, e));
    }

    {
        START_TIME(s);
        auto f = fibo_Three(n);
        STOP_TIME(e);
        printf("3 Fibo of %d is %d. It tool: %f ms\n", n, f, DIFF_IN_MS(s, e));
    }

    return 0;
}

