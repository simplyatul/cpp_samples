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
        if(!root) return {};
        //vector<vector<int>> ans(12); // some large hard coded value
        vector<vector<int>> ans;
        queue<TreeNode*> loQ; 
        loQ.push(root);
        int cLevel = 0;
        while(!loQ.empty()) {
            int nodesAtCurrLevel = pow(2, cLevel);
            vector<int> clVector; // current level vector
            for(int i=0; i<nodesAtCurrLevel; ++i) {
                if(loQ.empty()) continue;
                auto cNode = loQ.front();
                loQ.pop();
                clVector.push_back(cNode->val);
                //ans[cLevel].push_back(cNode->val);
                if(cNode->left) loQ.push(cNode->left);
                if (cNode->right) loQ.push(cNode->right);
            }
            ++cLevel;
            ans.push_back(clVector);
        }
        return ans;
    }
};

TreeNode* makeTree_One() {
    TreeNode* l15 = new TreeNode(15);
    TreeNode* l7 = new TreeNode(7);
    TreeNode* i20 = new TreeNode(20, l15, l7);
    TreeNode* i9 = new TreeNode(9);
    TreeNode* root = new TreeNode(3, i9,i20);
    return root;
}

TreeNode* makeTree_Two() {
    TreeNode* l15 = new TreeNode(15);
    TreeNode* l7 = new TreeNode(7);
    TreeNode* i20 = new TreeNode(20, l15, l7);

    TreeNode* l99 = new TreeNode(99);
    TreeNode* l5 = new TreeNode(5);
    TreeNode* i9 = new TreeNode(9, l99, l5);

    TreeNode* root = new TreeNode(3, i9, i20);
    return root;
}

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

    for(auto v: ans) {
        for(auto i: v) {
            cout << i << " ";
        }
        cout << endl;
    }
    cout << endl;
    return 0;
}