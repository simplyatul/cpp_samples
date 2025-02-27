#include <iostream>
#include <vector>

/*
 * Q: https://leetcode.com/problems/zigzag-conversion/description/?envType=study-plan-v2&envId=top-interview-150
 * https://walkccc.me/LeetCode/problems/6/
*/

using namespace std;

class Solution {
public:
    string convertOne(string s, int numRows) {
        string ans;
        vector<vector<char>> rows(numRows);
        int k = 0;
        int direction = (numRows == 1) - 1;

        for (const char c : s) {
            rows[k].push_back(c);
            if (k == 0 || k == numRows - 1)
                direction *= -1;
            k += direction;
        }

        for (const vector<char>& row : rows)
            for (const char c : row)
                ans += c;

        return ans;
    }
};

int main() {
    vector < string > in = {
        {"PAYPALISHIRING"}
    };

    Solution s;
    for(auto i: in) {
        s.convertOne(i, 3);
        cout << endl;
    }

}