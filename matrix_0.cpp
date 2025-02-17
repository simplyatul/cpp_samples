#include <iostream>
#include <vector>
#include "matrix_utils.h"

/*
 * Q: // Q: https://leetcode.com/problems/spiral-matrix/description/
 * Given an m x n matrix, return all elements of the matrix in spiral order.
 * 
 * https://walkccc.me/LeetCode/problems/54/
*/

using namespace std;

#define ADD_IN_SPIRAL spiralVector.push_back(matrix[r][c]); elemsToVisit--;
#define CHECK (elemsToVisit>0)

#define SIZE_CHECK (ans.size() < rLen*cLen)
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        if(matrix.empty()) {
            return {};
        }
        vector<int> ans;
        int rLen = matrix.size();
        int cLen = matrix[0].size(); 
        int r1=0;
        int r2=rLen-1;
        int c1=0;
        int c2=cLen-1;

        while(SIZE_CHECK) {
            for(int i=c1; i <= c2 && SIZE_CHECK; ++i) {
                ans.push_back(matrix[r1][i]);
            }

            for (int j=r1+1; j <= r2 && SIZE_CHECK; ++j) {
                ans.push_back(matrix[j][c2]);
            }

            for (int i=c2-1; i >= c1 && SIZE_CHECK; --i) {
                ans.push_back(matrix[r2][i]);
            }

            for (int j=r2-1; j > r1 && SIZE_CHECK; --j) {
                ans.push_back(matrix[j][c1]);
            }

            r1++;r2--;
            c1++;c2--;
        }

        return ans;

    }
};

int main() {
    vector < vector< vector<int> >> metrics = {
        {{4},{-33},{-99}},
        {{1,2,3}},
        {{1,2,3,4},{5,6,7,8},{9,10,11,12}},
        {{1,2,3},{4,5,6},{7,8,9}}
    };
    Solution s;
    for(auto m: metrics) {
        cout << endl << "Orig Matrix" << endl;
        printMatrix(m);
        cout << endl;
        auto arr = s.spiralOrder(m);
        cout << "Spiral Order: " << endl ;
        for(auto e: arr) {
            cout << e << " " ;
        }
        cout << endl << endl;
        
    }
    return 0;
}