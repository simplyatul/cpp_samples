/*
 * run: g++ dp-2.cpp
 * Q: 
 * Ref: 
 */

#include <cstdio>
#include <vector>
#include <unistd.h>
#include "common.h"
#include <climits>

using namespace std;

/*
 * Q: 322. Coin Change
 * Ref:
 * https://leetcode.com/problems/coin-change/description/?envType=study-plan-v2&envId=top-interview-150
 * https://www.youtube.com/watch?v=A3FHNCAkhxE&list=PLDzeHZWIZsTomOPnCiU3J95WufjE36wsb&index=4
 * 
 */

class Solution {
public:

    // Recursion
    int solve1(vector<int>& coins, int amount, int c) {
        if(amount == 0)
            return c;
        if(amount < 0)
            return INT_MAX;

        int minCoins = INT_MAX;
        for(int i=0; i< coins.size(); ++i) {
            int sol = solve1(coins, amount-coins[i], c+1);
            minCoins = min(minCoins, sol);
        }

        return minCoins;
    }

    int coinChangeOne(vector<int>& coins, int amount) {
        auto ans = solve1(coins, amount, 0);
        return ans == INT_MAX? -1: ans;
    }

    // Recursion + Memoization
    int solve2(vector<int>& coins, int amount, int c, 
                vector<int> &dp) {
        if(amount == 0) 
            return c;

        if(amount < 0)
            return INT_MAX;

        if(dp[amount] != INT_MAX)
            return dp[amount];

        int minCoins = INT_MAX;
        for(int i=0; i< coins.size(); ++i) {
            int sol = solve2(coins, amount-coins[i], c+1, dp);
            minCoins = min(minCoins, sol);
        }
        dp[amount] = minCoins;

        return minCoins;
    }

    // ToDo: Fix this
    int coinChangeTwo(vector<int>& coins, int amount) {
        vector<int> dp(amount+1, INT_MAX);
        auto ans = solve2(coins, amount, 0, dp);
        return ans == INT_MAX? -1: ans;

    }

    int solve3(vector<int>& coins, int amount) {
        vector<int> dp(amount+1, INT_MAX);

        dp[0] = 0;

        for(int i =0; i<= amount; i++) {
            for(int j=0; j<coins.size(); j++) {
                if(i-coins[j] >= 0 && 1 + dp[i-coins[j]] != INT_MAX )
                    dp[i] = min(dp[i], 1 + dp[i-coins[j]]);
            }
        }

        return dp[amount];
    }

    // Using Tabulation => Bottom-Up approach
    int coinChangeThree(vector<int>& coins, int amount) {
        return solve3(coins, amount);
    }
};

int main() {
    
    Solution s;
    {
        vector<int> coins = {1, 2, 5};
        int amt = 30;
        {
            START_TIME(start);
            auto res = s.coinChangeOne(coins, amt);
            STOP_TIME(end);
            printf("Min coins  %d\n", res); 
            printf("coinChangeOne Took %f ms\n\n\n", DIFF_IN_MS(start, end));
        }

        {
            START_TIME(start);
            auto res = s.coinChangeTwo(coins, amt);
            STOP_TIME(end);
            printf("Min coins  %d\n", res); 
            printf("coinChangeTwo Took %f ms\n\n\n", DIFF_IN_MS(start, end));
        }

        {
            START_TIME(start);
            auto res = s.coinChangeThree(coins, amt);
            STOP_TIME(end);
            printf("Min coins  %d\n", res); 
            printf("coinChangeThree Took %f ms\n\n\n", DIFF_IN_MS(start, end));
        }

    }
    return 0;
}

