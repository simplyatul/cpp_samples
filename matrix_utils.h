#ifndef __MATRIX_UTILS_H__
#define __MATRIX_UTILS_H__ 1

#include <iostream>
#include <vector>

using namespace std;

void printMatrix(vector<vector<int>>& matrix) {
    int rLen = matrix.size();
    int cLen = matrix[0].size();
    for(int i=0; i<rLen; ++i) {
        for(int j=0; j<cLen; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

#endif // end of __MATRIX_UTILS_H__