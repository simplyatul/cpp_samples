/*
 * run: g++ dp-0.cpp
 * Q: Climbing Stairs
 * Ref: https://leetcode.com/problems/climbing-stairs/description/?envType=study-plan-v2&envId=top-interview-150
 */

#include <cstdio>
#include <vector>
#include <unistd.h>
#include "common.h"

using namespace std;

class Solution {
public:
    /*
     * Using Recursion
     */
    int climbStairsOne(int n) {
        if(n == 0) return 0;
        if(n == 1) return 1;
        if(n == 2) return 2;

        return climbStairsOne(n-1) + climbStairsOne(n-2);
    }

    /*
     * DP w/ Tabulation + Space Optimization
     */

    int climbStairsTwo(int n) {
        // steps req to climb 0 stair
        if(n == 0) return 0; 
        // steps req to climb 1 stair
        if(n == 1) return 1;
        // steps req to climb 2 stairs
        if(n == 2) return 2;

        /* In same way, steps required to climb
        * n stairs = steps required to climb (n-1) stairs => prev1
        *            +
        *            steps required to climb (n-2) stairs => prev2
        *
        */
        
        int prev1 = 2;
        int prev2 = 1;
        int curr = 0;
        for(int i=3; i<=n; ++i) {
            curr = prev1 + prev2;
            prev2 = prev1;
            prev1 = curr;
        }
        return curr;
    }
};

int main() {
    int n = 20;
    Solution s;
    {
        START_TIME(start);
        auto res = s.climbStairsOne(n); // Takes ~5-6 sec if n = 45
        STOP_TIME(end);
        printf("Result: %d ways to climb %d stairs\n", res, n); 
        printf("climbStairsOne Took %f ms\n", DIFF_IN_MS(start, end));
    }

    {
        START_TIME(start);
        auto res = s.climbStairsTwo(n);
        STOP_TIME(end);
        printf("Result: %d ways to climb %d stairs\n", res, n); 
        printf("climbStairsTwo Took %f ms\n", DIFF_IN_MS(start, end));
    }

    return 0;
}

