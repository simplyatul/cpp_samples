
#include <iostream>
#include <vector>

using namespace std;

/*
 * Q: Permutations
 * 
 * Refs:
 * https://leetcode.com/problems/permutations/description/?envType=study-plan-v2&envId=top-interview-150
 * https://www.youtube.com/watch?v=va3NEycUxsg&list=PLDzeHZWIZsTqBmRGnsCOGNDG5FY0G04Td&index=9
 * https://drive.google.com/file/d/1UcPqTr312lG5lffIPEB8rU7KKnZDDwAI/view
 * 
*/

class Solution {
private:
  void doPermutations(vector<int>& nums, const int idx, vector<vector<int>>& ans) {
    // base case
    if (idx >= nums.size()) {
      ans.push_back(nums);
      return;
    }

    for(int j=idx; j<nums.size(); ++j) {
      swap(nums[idx], nums[j]);
      doPermutations(nums, idx+1, ans);
      // backtrack
      swap(nums[idx], nums[j]);
    }
  }

public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> ans;
        int idx = 0;
        doPermutations(nums, idx, ans);
        return ans;
    }
};


int main() 
{
    vector<int> digits = {1,2,3,8};
    Solution s;
    auto ans = s.permute(digits);
    cout << "Elements in ans: " << ans.size() << endl;
    for(auto elem: ans) {
      for(auto i: elem)
        cout << i << ",";
      cout << "\n";
    }
    cout << "\n";
    return 0;
}

