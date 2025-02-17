#include <iostream>
#include <vector>

using namespace std;

#define ADD_IN_SPIRAL spiralVector.push_back(matrix[r][c]); elemsToVisit--;
#define CHECK (elemsToVisit>0)

#define SIZE_CHECK (ans.size() <= rLen*cLen)
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
            for(int i=0; i<= c2 && SIZE_CHECK; ++i) {
                ans.push_back(matrix[r1][i]);
            }

            for (int j=r1+1; j<= r2 && SIZE_CHECK; ++j) {
                ans.push_back(matrix[j][c2]);
            }

            for (int i=c2-1; i>= c1 && SIZE_CHECK; --i) {
                ans.push_back(matrix[r2][i]);
            }

            for (int j=r2-1; j>r1 && SIZE_CHECK; --j) {
                ans.push_back(matrix[j][c1]);
            }

            r1++;r2--;
            c1++;c2--;
        }

        return ans;


        int cycles=0;
        int elemsToVisit = rLen * cLen;
        vector<int> spiralVector;
        int r=0, c=0;

        // inc col
        while (CHECK & c < cLen)
        {
            ADD_IN_SPIRAL;
            c++;
        }
        c--;
        // inc row
        r++;
        while (CHECK & r < rLen)
        {
            ADD_IN_SPIRAL;
            r++;
        }
        r--;
        // dec col
        c--;
        while (CHECK & c >= 0)
        {
            ADD_IN_SPIRAL;
            c--;
        }
        c++;

        // now onwards go spiral
        int rcToSkip = 1; // rows/cols to skip
        while(CHECK) {
            // dec row
            while(r >= rLen-rcToSkip) {
                r--;
                ADD_IN_SPIRAL;
            }
        }

        return spiralVector;
        
    }
};

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

int main() {
    vector < vector< vector<int> >> metrics = {
        {{1,2,3,4},{5,6,7,8},{9,10,11,12}}
        //{{1,2,3},{4,5,6},{7,8,9}}
    };
    Solution s;
    for(auto m: metrics) {
        cout << "Orig Metrix" << endl;
        printMatrix(m);
        cout << endl;
        //cout << " Spriral Order: " << s.maxDepthThree(root) << endl;
        s.spiralOrder(m);
    }
    return 0;
}