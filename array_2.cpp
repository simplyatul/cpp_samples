#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
 * Q: 3 Sum
 * Ref: https://leetcode.com/problems/3sum/description/?envType=study-plan-v2&envId=top-interview-150
 */
const bool INDEXES = true;
const bool VALUES = false;

class Solution {
public:
    /*
     * inxOrVal
     *   true => returns indexes
     *   false => returns values
    */
    vector<int> twoSum(vector<int>& nums, int target, bool inxOrVal) {
        if (nums.size() < 2) return {};
        vector<int> ans;
        sort(nums.begin(), nums.end());
        int i = 0, j = nums.size()-1;
        while(i<j) {
            if(nums[i] + nums[j] == target) {
                if(inxOrVal == INDEXES) {
                    ans.emplace_back(i);
                    ans.emplace_back(j);
                }
                else { // VALUES
                    ans.emplace_back(nums[i]);
                    ans.emplace_back(nums[j]);
                }
                return ans;
            } else if (nums[i] + nums[j] > target) {
                --j;
            } else {
                ++i;
            }
        }
        return {};
    }

    vector<int> returnArrayExceptIndex(vector<int> num, int k) {
        vector<int> ans;
        if(k>0)
            ans.insert(ans.begin(), num.begin(), num.begin()+k);
        if(k < num.size()-1)
            ans.insert(ans.end(), num.begin()+k+1, num.end());
        return ans;
    }

    // This solution contains duplicates
    vector<vector<int>> threeSum(vector<int>& nums) {
        if (nums.size() < 3) return {};
        vector<vector<int>> finalAns;
        sort(nums.begin(), nums.end());
        for(int i=0; i<nums.size(); ++i) {
            auto subArr = returnArrayExceptIndex(nums, i);
            auto ans = twoSum(subArr, 0-nums[i], VALUES);
            if(ans.size() > 0) {
                ans.emplace_back(nums[i]);
                finalAns.emplace_back(ans);
            }
        }
        return finalAns;
    }
};

int main() {
    Solution s;
#if 0    
    cout << "\nTwoSum\n";
    vector<int> n1 = {2,7,11,15};

    auto ans = s.twoSum(n1, 9, INDEXES);
    for (auto i: ans) {
        cout << i << " ";
    }
    cout << "\n";
#endif
    cout << "\nthreeSum\n";
    vector<int> n2 = {-1,0,1,2,-1,-4};
    vector<vector<int>> ans1 = s.threeSum(n2);
    for (auto subarr: ans1) {
        for (auto i: subarr) {
            cout << i << " ";
        }
        cout << "\n";
    }
    cout << "\n";
    return 0;
}
