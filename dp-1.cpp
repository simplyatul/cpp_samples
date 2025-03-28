/*
 * run: g++ dp-0.cpp
 * Q: 746. Min Cost Climbing Stairs
 * Ref: https://leetcode.com/problems/min-cost-climbing-stairs/description/?envType=study-plan-v2&envId=leetcode-75
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
    int costof(const vector<int>& cost, const int n) {
        if(n == 0 || n == 1)
            return cost[n];

        auto n_minus_one = costof(cost, n-1);
        auto n_minus_two = costof(cost, n-2);
        auto minCost = cost[n] + min(n_minus_one, n_minus_two);
        return minCost;
    }

    // Recursion
    int minCostClimbingStairsOne(vector<int>& cost) {
        auto n = cost.size();
        auto ans = min(costof(cost, n-1), costof(cost, n-2));
        return ans;
    }

    int costof2(const vector<int>& cost, const int n, vector<int>& dp) {
        if(n == 0 || n == 1)
            return cost[n];
        if(dp[n] != -1) 
            return dp[n];
        auto n_minus_one = costof2(cost, n-1, dp);
        auto n_minus_two = costof2(cost, n-2, dp);
        dp[n] = cost[n] + min(n_minus_one, n_minus_two);
        return dp[n];
    }

    // Recursion + Memoization
    int minCostClimbingStairsTwo(vector<int>& cost) {
        auto n = cost.size();
        vector<int> dp(n+1, -1);
        auto ans = min(costof2(cost, n-1, dp), costof2(cost, n-2, dp));
        return ans;
    }

    int costof3(const vector<int>& cost) {
        auto n = cost.size() + 1;
        vector<int> dp(n, 0);
        dp[0] = cost[0];
        dp[1] = cost[1];

        for(int i=2; i < n; ++i) {
            dp[i] = cost[i] + min(dp[i-1], dp[i-2]);
        }

        return min(dp[n-1], dp[n-2]);
    }

    // w/ Space Optimization
    int minCostClimbingStairsThree(vector<int>& cost) {
        return costof3(cost);
    }

    int costof4(const vector<int>& cost) {
        auto n = cost.size() + 1;
        int prev2 = cost[0];
        int prev1 = cost[1];
        int curr = 0;
        for(int i=2; i <=n; ++i) {
            curr = cost[i] + min(prev1, prev2);
            prev2 = prev1;
            prev1 = curr;
        }

        return min(curr, prev1);
    }

    // w/ more Space Optimization
    int minCostClimbingStairsFour(vector<int>& cost) {
        return costof4(cost);
    }

};

int main() {
    
    Solution s;
    {
        // vector<int> cost = {10, 15, 20};
        vector<int> cost = {1,100,1,1,1,100,1,1,100,1};
        {
            START_TIME(start);
            auto res = s.minCostClimbingStairsOne(cost);
            STOP_TIME(end);
            printf("Min Cost Climbing Stairs %d\n", res); 
            printf("minCostClimbingStairsOne Took %f ms\n\n\n", DIFF_IN_MS(start, end));
        }

        {
            START_TIME(start);
            auto res = s.minCostClimbingStairsTwo(cost);
            STOP_TIME(end);
            printf("Min Cost Climbing Stairs %d\n", res); 
            printf("minCostClimbingStairsTwo Took %f ms\n\n\n", DIFF_IN_MS(start, end));
        }

        {
            START_TIME(start);
            auto res = s.minCostClimbingStairsThree(cost);
            STOP_TIME(end);
            printf("Min Cost Climbing Stairs %d\n", res); 
            printf("minCostClimbingStairsThree Took %f ms\n\n\n", DIFF_IN_MS(start, end));
        }

        {
            START_TIME(start);
            auto res = s.minCostClimbingStairsFour(cost);
            STOP_TIME(end);
            printf("Min Cost Climbing Stairs %d\n", res); 
            printf("minCostClimbingStairsFour Took %f ms\n\n\n", DIFF_IN_MS(start, end));
        }

    }
    return 0;
}

