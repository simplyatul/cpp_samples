#include <iostream>
#include <vector>

/*
 * Q: Word Search
 * Ref: https://leetcode.com/problems/word-search/description/?envType=study-plan-v2&envId=top-interview-150
 */
using namespace std;

class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        const int rows = board.size();
        const int cols = board[0].size();
        int k=0;
        for(int i=0; i<rows; ++i) {
            for(int j=0; j<cols; ++j) {
                if(board[i][j] == word[k]) {
                    vector<vector<int>> visited(rows, vector<int>(cols));
                    initVisited(visited);
                    bool ans = moveNext(board, word, k+1, i, j, visited);
                    if(true == ans)
                        return true;
                }
            }
        }

        return false;
    }

    bool moveNext(vector<vector<char>>& board, 
                string word, int wi, int r, int c,
                vector<vector<int>> visited) {
        visited[r][c] = 1;
        if(wi >= word.length())
            return false;
        // Neighbors - left, right, up, down
        vector<int> rNbr = {0,  0, -1,  1};
        vector<int> cNbr = {-1, 1,  0,  0};

        for(int d=0; d<4; ++d) {
            int nr = r+rNbr[d]; // next row
            int nc = c+cNbr[d]; // next col
            if (isValid(nr, nc, board, visited) && 
                board[nr][nc] == word[wi]) {
                if(wi == word.length()-1) {
                    // found
                    return true;
                }
                if (true == moveNext(board, word, wi+1, nr, nc, visited))
                    return true;
            }
        }
        return false;
    }

    bool isValid(int r, int c, 
            vector<vector<char>>& board,
            vector<vector<int>> visited) {
        const int rows = board.size();
        const int cols = board[0].size();

        if(r >=0 && r < rows &&
           c >=0 && c < cols &&
           visited[r][c] == 0
        )
            return true;
        
        return false;
    }

    void initVisited(vector<vector<int>>&  visited) {
        const int rows = visited.size();
        const int cols = visited[0].size();
        for(int i=0; i<rows; ++i)
            for(int j=0; j<cols; ++j)
                visited[i][j]=0;
    }

    void printBard(const vector<vector<char>>& board) {
        const int rows = board.size();
        const int cols = board[0].size();
        for(int i=0; i<rows; ++i) {
            for(int j=0; j<cols; ++j) {
                cout << board[i][j] << " ";
            }
            cout << "\n";
        }
    }
};

int main() {
    vector<vector<char>> board_1 = {
        {'A','B','C','E'},
        {'S','F','C','S'},
        {'A','D','E','E'}
    };

    vector<vector<char>> board_2 = {
        {'A','B','C','E'},
        {'S','F','C','S'},
        {'A','D','E','E'}
    };

    vector<vector<char>> board_3 = {
        {'A','B','C','E'},
        {'S','F','C','S'},
        {'A','D','E','E'}
    };

    Solution s;
    s.printBard(board_1);
    string word = "ABCCED";
    cout << word << " exist? " << s.exist(board_1, word) << endl;
    
    word = "FCEDFB";
    cout << word << " exist? " << s.exist(board_1, "FCEDFB") << endl;
    
    word = "SEE";
    s.printBard(board_2);
    cout << word << " exist? " << s.exist(board_2, word) << endl;

    word = "ABCB";
    s.printBard(board_3);
    cout << word << " exist? " << s.exist(board_3, word) << endl;
}