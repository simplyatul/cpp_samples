/*
Example test:   [3, 8, 2, 3, 3, 2]
Output (stderr):
terminate called after throwing an instance of 'std::bad_alloc'
  what():  std::bad_alloc
RUNTIME ERROR (tested program terminated with exit code 262)
*/

#include <iostream>
#include <vector>

using namespace std;

//#define DEBUG 

int solution(vector<int> &A) {
    int Max = 0;
    constexpr int RANGE = 1000000000;
    vector<int> B(RANGE+1, 0);

    for(auto i: A) {
        B[i]++;
        if(i> Max) {
            Max=i;
        }
    }

#ifdef DEBUG
    cout << "Max: " << Max << endl;
#endif

    for(int k=Max; k>0; --k)
    {
#ifdef DEBUG
        cout << B[k] << endl;
#endif
        if(B[k]==k)
            return k;
    }

    return 0;
};


int main() {
    vector< vector<int> > inputs = {
        {3,8,2,3,3,2},
        {7,1,2,8,2},
        {3,1,4,1,5},
        {5,5,5,5,5}
        //{2,2}
    };
    for(auto a: inputs) {
        cout << "Sol: " << solution(a) << endl;
    }
    return 0;
}

