/*
 * run: g++ divisible_by_digits.cpp
 * Problem statement: Given input n, find out how many digits in that input
 * can divide n.
 *
 * Input n = 232
 * Output should be 2.
 * 232 is divisible by 2 and 2 appears 2 times in 232
 *
 * Input n = 65
 * Output should be 1.
 * 65 is divisible by 5 only
 *
 * Input -8192
 * Output should be 3.
 * -8192 is divisible by 2, 1, 8 only
 *
 */

/* Constraints
 * 0 <= n <= 109
 * n does not contain 0
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int solution(int n) {
    unordered_map<char, int> result;
    string nstr = to_string(n);
    for (auto c: nstr) {
        //cout << c << endl;
        if('-' == c) continue;
        int d = int(c - '0');
        if(0==d) continue;
        if(0 == n%d) {
            // divisible by digit
            auto it = result.find(c);
            if(it != result.end()) {
                // key exists
                it->second = it->second + 1;
            } else {
                result[c]=1;
            }
        }
    }
    int c = 0;
    for (auto i = result.begin(); i != result.end(); i++) {
            cout << i->first << "       " << i->second << '\n';
            c = c+i->second;
    }

    //cout << c << endl;
    return c;
}

int main(int argc, char **argv) {
    int input = -122;
    cout << "Input: " << input << endl;
    int o = solution(input);
    cout << "Output: " << o << endl;
    return 0;
}

