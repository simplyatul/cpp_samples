
#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

/*
 * Q: Escape a Large Maze
 * 
 * Refs:
 * https://leetcode.com/problems/escape-a-large-maze/
 * 
 * 
*/
class Solution {
private:
    /*
     * MazeMax = 100, Time to Search = ~ 7 ms
     * MazeMax = 1000, Time to Search = ~ 687 ms
     * MazeMax = 2000, Time to Search = ~ 2740 ms
     * ToDo Optimize for higher values of Maze size 
     */
    const int MazeMax = 5;
    // four ways to move => left, right, up, down
    vector<int> rNbhr = {0, 0, -1, 1};
    vector<int> cNbhr = {-1, 1, 0, 0};

    bool isCurrPositionBlocked(const vector<vector<int>>& blocked, 
                    const vector<int> curr) {
      for (auto blk: blocked) {
        if(blk == curr) {
          return true;
        }
      }
      return false;
    }
    
    bool isCurrPositionOutOfGrid(const vector<int> curr) {
      if(curr[0] < 0 || curr[0] >= MazeMax ||
          curr[1] < 0 || curr[1] >= MazeMax)
          return true;

      return false;
    }
    bool isCurrPositionEqToTarget(const vector<int> curr, const vector<int> target) {
      if(curr == target)
        return true;
      return false;
    }

    bool isCurrPositionVisited(const vector<int> curr,
        vector<vector<int>> &visited) {
      for (auto v : visited) {
        if (v == curr)
          return true;
      }
      return false;
    }

    bool isPossible(vector<vector<int>>& blocked, 
        vector<int>& source, vector<int>& target, vector<vector<int>>& visited) {
        auto curr = source;

        // base
        if (isCurrPositionBlocked(blocked, curr) || isCurrPositionOutOfGrid(curr))
          return false;
        if(isCurrPositionEqToTarget(curr, target))
          return true;
        
        visited.push_back(curr);
        for(int i=0; i < rNbhr.size(); ++i) {
          vector<int> nextPosition = {curr[0]+rNbhr[i], curr[1]+cNbhr[i]};
          if (true == isCurrPositionVisited(nextPosition, visited))
            continue;
          if (true == isPossible(blocked, nextPosition, target, visited))
            return true;
        }

        return false;

    }
public:
    bool isEscapePossible(vector<vector<int>>& blocked, 
      vector<int>& source, vector<int>& target) {
        vector<vector<int>> visited;
      return isPossible(blocked, source, target, visited);
    }
};


int main() 
{
    cout << (1 + 199) * 199 / 2 << endl;
    vector<vector<int>> blocked = {
      {1, 1},
      {2, 0},
      {2, 1},
      {3, 3}
    };
    vector<int> source = {0, 3};
    vector<int> target = {3, 0};

    Solution s;
    auto start = chrono::high_resolution_clock::now();
    auto res = s.isEscapePossible(blocked, source, target);
    auto stop = chrono::high_resolution_clock::now();
    cout << "Is reachable: " << res << endl;
    cout << "Function took: " 
          << chrono::duration<double, std::milli>(stop-start).count() 
          << " ms";
    cout << "\n";
    return 0;
}

