
#include <iostream>
#include <vector>

using namespace std;

/*
 * Q: Letter Combinations of a Phone Number
 * 
 * Refs:
 * https://leetcode.com/problems/letter-combinations-of-a-phone-number/description/?envType=study-plan-v2&envId=top-interview-150
 * https://www.youtube.com/watch?v=tWnHbSHwNmA&list=PLDzeHZWIZsTqBmRGnsCOGNDG5FY0G04Td&index=8
 * 
 * 
*/


class Solution {
private:
  vector<string> numPad = {
    "", 
    "",
    "abc",
    "def",
    "ghi",
    "jkl",
    "mno",
    "pqrs",
    "tuv",
    "wxyz"
    };
  void lc(const string digits, const int index, string output, vector<string> &ans) {
      // base case
      if(index >= digits.size()) {
        ans.push_back(output);
        return ;
      }

      int ixd = digits[index] - '0';
      string numString = numPad[ixd];
      for(auto c: numString) {
        output.push_back(c);
        lc(digits, index+1, output, ans);
        //output.erase(output.cend()-1);
        output.pop_back(); // => backtrack
      }
  }

public:
    vector<string> letterCombinations(string digits) {
        if(digits.length() == 0)
          return {};
        vector<string> ans;
        int index = 0;
        string output;

        lc(digits, index, output, ans);
        return ans;
    }
};


int main() 
{
    string digits = "29";
    Solution s;
    auto ans = s.letterCombinations(digits);
    cout << "Elements in ans: " << ans.size() << endl;
    for(auto elem: ans) {
        cout << elem << " ";
    }
    cout << "\n";
    return 0;
}

