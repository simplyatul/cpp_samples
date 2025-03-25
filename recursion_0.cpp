
#include <iostream>
#include <vector>

using namespace std;

/*
 * Q: Given an integer array nums of unique elements, return all 
 * possible (the power set). The solution set must not contain duplicate 
 * subsets. Return the solution in any order.
 * 
 * Power set => set of all subsets
 * Elements in power set = 2^n
 * 
 * Refs: 
 * https://leetcode.com/problems/subsets/description/
 * https://drive.google.com/file/d/1VPaZB14_cpl1yx8f5yyvNdHJuE42CEpG/view
 * https://www.youtube.com/watch?v=V0IgCltYgg4&list=PLDzeHZWIZsTqBmRGnsCOGNDG5FY0G04Td&index=7&pp=iAQB
 * 
 * 
*/

class Solution {
private:
    void findSubSets(vector<int>& nums, const int index, 
            vector<int> output, vector<vector<int>>& ans) {
        if(index >= nums.size()) {
          ans.push_back(output);
          return;
        }

        // exclude
        findSubSets(nums, index+1, output, ans);

        // include
        output.push_back(nums[index]);
        findSubSets(nums, index+1, output, ans);
    }

public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> ans;
        int index = 0;
        vector<int> output;

        findSubSets(nums, index, output, ans);
        return ans;
    }
};


int main() 
{
    vector<int> set1 = {};
    Solution s;
    auto ans = s.subsets(set1);
    cout << "Size of power set: " << ans.size() << endl;
    for(auto set: ans) {
      for(auto elem: set) {
        cout << elem << " ";
      }
      cout << "\n";
    }
    return 0;
}

