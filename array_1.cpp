#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Increasing Triplet Subsequence
// Q: https://leetcode.com/problems/increasing-triplet-subsequence/?envType=study-plan-v2&envId=leetcode-75
// 

class Solution {
public:
    bool increasingTripletOne(vector<int> &nums)
    {
        int i = 0;
        int j = 0;
        int k = 0;
        int size = nums.size();
        if(size <= 2) return false;

        while (i < size)
        {
            // find i
            while (i < size && nums[i] > nums[i + 1])
                ++i;
            if (i >= size) return false;
            j = i + 1;
            k = j + 1;
            // validate k
            while (k < size && nums[k] < nums[j] && nums[k] > nums[i])
                ++k;
            if (k >= size) return false;
            if (nums[k] < nums[i])
            {
                i = k;
                continue;
            }
            return true;
        }

        vector<int> flowerbed; int n;

        if (flowerbed[i] == 0 && 
            (i == 0 || flowerbed[i - 1] == 0) &&
            (i == flowerbed.size() - 1 || flowerbed[i + 1] == 0)
            )

            return false;
    }
    // https://walkccc.me/LeetCode/problems/334/
    bool increasingTripletTwo(vector<int> &nums)
    {
        int first = INT_MAX;
        int second = INT_MAX;

        for (const int num : nums)
            if (num <= first)
                first = num;
            else if (num <= second) // first < num <= second
                second = num;
            else
                return true; // first < second < num (third)

        return false;
    }

};

int main() {
    
    vector< vector<int> > in = {
        {-2,-23,5,0,4,6},
        {-2,1,5,0,4,6},
        {10,2},
        {20,10,15,0,4,6},
        {2,1,5,0,4,6},
        {1,2,3},
        {890, 880, 870, 500, 750, 740, 735, 400, 300}
    };

    Solution *s = new Solution();
    for(auto a: in) {
        cout << s->increasingTripletTwo(a) << endl; 

    }
    return 0;
}
