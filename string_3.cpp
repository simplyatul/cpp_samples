#include <iostream>
#include <vector>

/*
 * Q: https://leetcode.com/problems/string-compression/description/
 * 
*/

using namespace std;


class Solution {
public:
    // https://walkccc.me/LeetCode/problems/443/
    int compressTwo(vector<char> &chars)
    {
        int ans = 0;

        for (int i = 0; i < chars.size();)
        {
            const char letter = chars[i];
            int count = 0;
            while (i < chars.size() && chars[i] == letter)
            {
                ++count;
                ++i;
            }
            chars[ans++] = letter;
            if (count > 1)
                for (const char c : to_string(count))
                    chars[ans++] = c;
        }

        return ans;
    }

    int compress(vector<char> &chars)
    {
        if (chars.size() == 0)
            return 0;
        int i = 0;

        // find start and end indexes
        int end = 0;
        int digitsAdded = 0;
        int len = chars.size();
        while (end < chars.size())
        {
            int start = end;
            for (; end < chars.size(); ++end)
                if (chars[end] != chars[end + 1])
                    break;

            if(start == end) {
                end++;
                continue;
            }

            if (end > start)
            {
                digitsAdded = replace(start, end, chars);
                end = start + digitsAdded + 1;
                //len = chars.size();
            }
        }
        return chars.size();
    }

    int replace(int start, int end, vector<char>& chars) {
        char c = chars[start];
        if(end >= chars.size())
            end = chars.size()-1;
        int total = end - start + 1;
        string s = to_string(total);
        s.insert(s.begin(), c);

        chars.erase(chars.begin()+start, chars.begin()+end+1);
        chars.insert(chars.begin()+start, s.begin(), s.end());

        return s.size()-1;

    }
};

void Print(const std::vector<char>& v){
    for (auto it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
}

int main() {
    vector < vector<char> > samples = {
        //{'a','b'},
        {'a','a','a','a','b','b'}
        //{'a','a','b','b', 'c', 'c', 'c'}
        //{'a','b','b', 'b', 'b', 'b', 'c', 'c', 'c'}
        //{'a','b','b','b','b','b','b','b','b','b','b','b','b'}
        //{'a','r','b','b','d','d','d','d','d','d','d','d','d','d','d','d','d','d', 'k'},
    };
    Solution s;
    for(auto i: samples) {
        cout << "In:  "; 
        Print(i);
        cout << endl;

        auto size = s.compressTwo(i);
        //auto size = s.replace(0,1, i);

        cout << "Out: "; 
        Print(i);
        cout << endl;
        cout << "Size: " << size << endl;
    }
    return 0;
}