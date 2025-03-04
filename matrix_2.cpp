#include <iostream>
#include <vector>

/*
 * Q: https://leetcode.com/problems/number-of-islands/description/?envType=study-plan-v2&envId=top-interview-150
 * Ref: https://www.geeksforgeeks.org/find-the-number-of-islands-using-dfs/
 */
using namespace std;

class Solution {
public:
    int numIslands(const vector<vector<char>>& grid) {
        int count = 0 ;
        int rows = grid.size();
        int cols = grid[0].size();

        printGrid(grid);
        vector<vector<int>> visited(rows, vector<int>(cols));
        for(int i=0; i<rows; ++i)
            for(int j=0; j<cols; ++j)
                visited[i][j] = 0;

        // traverse all vertices of grid
        for(int i=0; i<rows; ++i)
            for(int j=0; j<cols; ++j) {
                if(grid[i][j] == '1' && !visited[i][j]) {
                    dfs(grid, visited, i, j);
                    count++;
                }
            }

        return count;
    }

private:
    void dfs(const vector<vector<char>>& grid, vector<vector<int>> &visited,
            const int r, const int c) {
        int rows = grid.size();
        int cols = grid[0].size();

        visited[r][c] = 1;
        // check all neighbors in 8 directions
        vector<int> rNbh = {-1, -1, -1, 0,  0,  1, 1, 1};
        vector<int> cNbh = {-1,  0,  1, -1, 1, -1, 0, 1};

        for(int k=0; k<8; ++k) {
            if (isValid(r+rNbh[k], c+cNbh[k], rows, cols, visited, grid)) {
                dfs(grid, visited, r+rNbh[k], c+cNbh[k]);
            }
        }
    }

    bool isValid(const int r, const int c, const int rows, const int cols, 
            const vector<vector<int>> &visited, 
            const vector<vector<char>>& grid) {
        if( r < rows && r >= 0 &&
            c < cols && c >= 0 &&
            !visited[r][c] &&
            grid[r][c] == '1'
          )
            return true;
        return false;
    }

    void printGrid(const vector<vector<char>>& grid) {
        const int rows = grid.size();
        const int cols = grid[0].size();
        for(int i=0; i<rows; ++i) {
            for(int j=0; j<cols; ++j) {
                cout << grid[i][j] << " ";
            }
            cout << "\n";
        }
    }
};

int main() {
    vector<vector<char>> grid_4 = {
        {'0','0'},
        {'0','1'}
    };

    vector<vector<char>> grid_3 = {
        {'1','0','1'},
        {'0','0','1'},
        {'0','0','0'}
    };

    vector<vector<char>> grid_1 = {
        {'1','1','1','1','0'},
        {'1','1','0','1','0'},
        {'1','1','0','0','0'},
        {'0','0','0','0','0'}
    };

    vector<vector<char>> grid_2 = {
        {'1','1','0','0','0'},
        {'1','1','0','1','0'},
        {'0','0','0','0','0'},
        {'1','0','0','1','1'}
    };

    Solution s;
    cout << s.numIslands(grid_4) << endl;
}