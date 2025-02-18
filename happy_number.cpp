#include <iostream>
#include <vector>
#include  <unordered_set>
#include <bits/stdc++.h>


/*
 * Q: https://leetcode.com/problems/happy-number/description/
 * Happy Number
 * SolutionTwo => https://walkccc.me/LeetCode/problems/202/
*/

using namespace std;

class Solution {
public:
    virtual bool isHappy(int n) = 0;
};

class SolutionTwo: public Solution {
 public:
  bool isHappy(int n) {
    int slow = squaredSum(n);
    int fast = squaredSum(squaredSum(n));
    cout << "slow: " << slow << " fast: " << fast << "\n";

    while (slow != fast) {
      slow = squaredSum(slow);
      fast = squaredSum(squaredSum(fast));
      cout << "slow: " << slow << " fast: " << fast << "\n";
    }

    return slow == 1;
  }

 private:
  int squaredSum(int n) {
    int sum = 0;
    while (n > 0) {
      sum += pow(n % 10, 2);
      n /= 10;
    }
    return sum;
  };
};

class SolutionOne: public Solution {
    unordered_set<int> ssdSet;
public:
    bool isHappy(int n) {
        ssdSet.clear();
        if (n<=0) return false;
        int ssd = n;
        ssdSet.insert(n);
        while(ssd!=1) {
            auto k = ssds(ssd);
            cout << k << "\n";
            if (ssdSet.find(k) != ssdSet.end()) 
                return false; // Found
            else 
                ssdSet.insert(k);
            ssd=k;
        }
        cout << "\n";
        return true;
    }
    
    // sum of the squares of its digits.
    int ssds(int n) {
        int ssd = 0; 
        while(n > 0) {
            int k = n%10;
            ssd += k*k;
            n = n/10;
        }
        return ssd;
    }
};

int main() {
    int k = 3;
    vector < int > input = {
        {19}
    };
    Solution * s = new SolutionOne();
    for(auto i: input) {
        bool ans = s->isHappy(i);
        cout << i << " " << "isHappy: " << ans << endl;

        s = new SolutionTwo();
        ans = s->isHappy(i);
        cout << i << " " << "isHappy: " << ans << endl;
    }
    return 0;
}