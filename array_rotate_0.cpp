#include <iostream>
#include <vector>
#include <map>

using namespace std;

// Rotate Array by k steps
// Q: https://leetcode.com/problems/rotate-array/description/?envType=study-plan-v2&envId=top-interview-150
// Other Sol => https://walkccc.me/LeetCode/problems/189/
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int32_t n = nums.size(); 

        if (k<=0 || k==n) return;

        if(k > n){
            k = k % n; 
        }

        reverse(nums, 0, n-k-1);
        reverse(nums, n-k, n-1);
        reverse(nums, 0, n-1);
    }

    void reverse(vector<int>& nums, int32_t sIndex, int32_t eIndex) {
        if (sIndex > eIndex || eIndex >= nums.size())
            return; 
        while(eIndex > sIndex) {
            swap(nums[sIndex++], nums[eIndex--]);
        }
    }
};

int main() {
    int k=3;
    map<int, vector<int> > in = {
        {1, {-1, 22}},
        {3, {1,2,-3}},
        {3, {1,2,3,5}},
        {3, {1,2,3,4,5,6,7}}
    };

    Solution *s = new Solution();
    for(auto a: in) {
        s->rotate(a.second, a.first); 
        //s->reverse(a, 0, 3);
        for (auto elem: a.second) {
            cout << elem << " ";
        }
        cout << endl;
    }
    return 0;
}
