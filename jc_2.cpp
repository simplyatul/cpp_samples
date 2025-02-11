#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

//#define DEBUG 

int solution(vector<int> &A) {
    unordered_map<int, int> result;

    for(auto i: A) {
        auto it = result.find(i);
        if(it != result.end()) {
            // key exists
            it->second = it->second + 1;
        } else {
            result[i]=1;
        }
    }

    int MaxVal = 0;
    for (auto i = result.begin(); i != result.end(); i++) {
        if(i->first == i->second) {
            if(i->first > MaxVal) {
                MaxVal = i->first;
            }
        }
    }
   
    return MaxVal;
};


int main() {
    vector< vector<int> > inputs = {
        {3,8,2,3,3,2},
        {7,1,2,8,2},
        {3,1,4,1,5},
        {5,5,5,5,5},
        {2,2,3,3,3,10,10,10,10,10,10,10,10,10,10,1,55,99,8},
        {2,2}
    };
    for(auto a: inputs) {
        cout << "Sol: " << solution(a) << endl;
    }
    return 0;
}

