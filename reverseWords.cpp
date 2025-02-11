#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// Problem Description: https://leetcode.com/problems/reverse-words-in-a-string/description/
// Credits: https://walkccc.me/LeetCode/problems/151/

using namespace std;

//#define DEBUG 
#define SPACE ' '

class Solution {
public:
    virtual string reverseWords(string s) = 0;
};

/*
 * SolutionTwo solves problem in place.
 * Takes O(1) space
 */

class SolutionTwo: public Solution {
public:
    string reverseWords(string s) {
        std::reverse(s.begin(), s.end());
        reverseEachWords(s);
        trimSpaces(s);
        return s;
    }
private:
    void reverseEachWords(string &s) {
        int i=0;
        int j=0;
        int n=s.length();

        while (i < n) {
            while (i < j || (i < n && s[i] == ' '))  // Skip the spaces.
                ++i;
            while (j < i || (j < n && s[j] != ' '))  // Skip the spaces.
                ++j;
            // i points to start of the word
            // j points to end of the word
            reverse(s.begin() + i, s.begin() + j);  // Reverse the word.
        }
    }

    void trimSpaces(string &s) {
        int i = 0;
        int j = 0;
        int n = s.length();

        while (j < n) {
            while (j < n && s[j] == ' ')  // Skip the spaces.
                ++j;
            while (j < n && s[j] != ' ')  // Keep non spaces
                s[i++] = s[j++];
            while (j < n && s[j] == ' ')  // Skip the spaces.
                ++j;
            if (j < n)  // Keep only one space.
                s[i++] = ' ';
        }

        s = s.substr(0, i);
    }
};

/*
 * SolutionOne takes O(n) additional space
 */

class SolutionOne: public Solution {
public:
    string reverseWords(string s) {
        int len = s.length();
        len-=1;
        vector <string> vec;
        while(len>=0) {
            if (SPACE == s[len]) {
                --len;
                continue;
            }
            string word;
            while(len>=0 && SPACE != s[len]) {
                word.insert(0, 1, s[len]);
                --len;
            }
            //vec.insert(vec.begin(), word);
            vec.insert(vec.end(), word);
            --len;
        }
        s.clear();
        int32_t noOfWords = vec.size();
        for(auto w: vec) {
            s.insert(s.length(), w);
            if(--noOfWords != 0)
                s.insert(s.length(), " ");
        }
        return s;
    }
};

int main() {
    vector< string > inputs = {
        {"w1  "},
        {"a"},
        {"a good   example"},
        {"the sky is blue"},
        {"  hello world  "}
        

    };
    // Solution *s = new SolutionOne();
    Solution *s = new SolutionTwo();
    for(auto a: inputs) {
        cout << "Sol: " << s->reverseWords(a) << endl;
    }
    return 0;
}

