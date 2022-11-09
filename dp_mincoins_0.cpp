/*
 * run: g++ dp_mincoins_0.cpp --std=C++17
 * given n, find minimum number of coins required from set of m
 * e.g. n = 18, n = [7, 5, 1] => min 4 coins require to build 18
 * This solution uses recursion
 */


#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

int n = 1;
const std::vector<int> m = {4, 4, 2};

int minCoins(const int n) {
    if (n == 0) return 0;

    int coins = INT_MAX;
    for (int i=0; i < std::size(m); i++) {
        auto sumLeft = n-m[i];
        if (sumLeft >= 0) {
            int part = minCoins(sumLeft);

            if (INT_MAX != part && part+1 < coins) {
                coins = part+1;
            }
        }
    }
    return coins;
}

int main() {

    std::cout << "sizeof array: " << std::size(m) << '\n';
    std::cout << "Int Max: " << INT_MAX << std::endl;
    std::cout << "----------------------" << endl;
    int c = minCoins(n);
    std::cout << "minCoins returns: " << c << '\n';
    std::cout << "Coins require: " << ((INT_MAX==c)? 0 : c) << '\n';
    return 0;
}
