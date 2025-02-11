#include <iostream>
#include <vector>
using namespace std;

//define DEBUG

int solution(vector<int> &A) {
    int lastSeen = -1;
    int secondLastSeen = -1;
    int ans = 0;
    int temp = 0;
    int newCnt = 0;

    for (auto const curr : A) {
        if (curr == lastSeen || curr == secondLastSeen) {
            temp++;
        } else {
            temp = newCnt + 1;
        }

        if (curr == lastSeen) {
            newCnt++;
        } else {
            newCnt = 1;
            secondLastSeen = lastSeen;
            lastSeen = curr;
        }

#ifdef DEBUG
        cout << "lastSeen: " << lastSeen << endl;
        cout << "secondLastSeen " << secondLastSeen << endl;
        cout << "newCnt " << newCnt << endl;
#endif
        ans = max(temp, ans);
    }
    return ans;
}

int main() {
    vector< vector<int> > inputs = {
        {-13},
        {4,2,2,4,2},
        {1,2,3,2},
        {0,5,4,4,5,12},
        {4,4},

        {-1,100,-2,-6,-6,-2}
    };
    for(auto a: inputs) {
        cout << "Sol: " << solution(a) << endl;
    }
    return 0;
}


