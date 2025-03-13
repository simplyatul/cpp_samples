#include <iostream>
#include <vector>
#include <queue>
#include <bits/stdc++.h>
#include "tree_utils.h"
#include <unordered_map>


using namespace std;

/*
 * Q: Binary Tree Level Order Traversal
 * https://leetcode.com/problems/binary-tree-level-order-traversal/description/?envType=study-plan-v2&envId=top-interview-150
 */

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        return levelOrderTraversal(root);
    }
};

int main() {
    TreeNode* r1 = makeTree_Two();
    cout << "preOrderTraversal...";
    cout << endl;
    preOrderTraversal(r1);
    cout << endl;
    Solution s;
    auto ans = s.levelOrder(r1);
    cout << "levelOrderTraversal...";
    cout << endl;
    printLevelOrderTraversal(r1);
    cout << endl;
    return 0;
}