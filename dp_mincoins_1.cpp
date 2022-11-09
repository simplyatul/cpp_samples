/*
 * run: g++ dp_mincoins_1.cpp --std=C++17
 * dynamic programming tech applied on dp_mincoins_0.cpp
 * Time Complexity is O(m.n)
 */


#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

int n = 8;
const std::vector<int> m = {4, 4, 2};
std::vector<int> resArr(n+1, -1);

int minCoins(const int n) {
    if (n == 0) return 0;

    int coins = INT_MAX;
    for (int i=0; i < std::size(m); i++) {
        auto sumLeft = n-m[i];
        int part = 0;

        if (sumLeft >= 0) {
            if (-1 == resArr[sumLeft]) {
                part = minCoins(sumLeft);
            } else {
                part = resArr[sumLeft];
            }

            if (INT_MAX != part && part+1 < coins) {
                coins = part+1;
            }
        }
    }
    return (resArr[n] = coins);
}

int main() {

    std::cout << "sizeof array: " << std::size(m) << '\n';
    std::cout << "Int Max: " << INT_MAX << std::endl;
    std::cout << "----------------------" << endl;
    int c = minCoins(n);
    for (auto x: resArr) cout << x << " ";
    cout << endl;
    std::cout << "minCoins returns: " << c << '\n';
    std::cout << "Coins require: " << ((INT_MAX==c)? 0 : c) << '\n';
    return 0;
}
