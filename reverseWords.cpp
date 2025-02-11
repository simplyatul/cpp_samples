#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// Problem Description: https://leetcode.com/problems/reverse-words-in-a-string/description/

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
        return s;
        int len = s.length(); 
        std::cout << "len: " << s.length() << "\n";
        len-=1;
        int32_t endPos=0, startPos=0;
        while (len>0)
        {
            string word;
            // Prep a word until 
            if (SPACE == s[len]) {
                s.pop_back();
                std::cout << s.length() << "\n";
                --len;
                continue;
            }
            else {

                while(SPACE != s[len]) {
                    word.insert(0, 1, s[len]);
                    s.pop_back();
                    --len;
                }

                s.insert(0, word);
            }

            /* code */
        }
        
        
        return s;


        
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
        {"a"},
        {"a good   example"},
        {"the sky is blue"},
        {"w1  "},
        {"  hello world  "}
        

    };
    Solution *s = new SolutionOne();
    //Solution *s = new SolutionTwo();
    for(auto a: inputs) {
        cout << "Sol: " << s->reverseWords(a) << endl;
    }
    return 0;
}

