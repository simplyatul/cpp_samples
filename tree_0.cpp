#include <iostream>
#include <vector>
#include <queue>
#include "tree_utils.h"

using namespace std;

// Q: Given the root of a binary tree, return its maximum depth
// Q: https://leetcode.com/problems/maximum-depth-of-binary-tree/description/

int maxDepth = 0;

void findDepthOne(TreeNode* root, int h) {
    if(!root) return;
    //cout << root->val << " ";
    root->h = h+1;
    if(maxDepth < root->h) 
        maxDepth = root->h;
    findDepthOne(root->left, root->h);
    findDepthOne(root->right, root->h);
};

void findDepthTwo(TreeNode* root, int h) {
    if(!root) return;

    if(maxDepth < h+1) 
        maxDepth = h+1;
    findDepthTwo(root->left, h+1);
    findDepthTwo(root->right, h+1);
};


class Solution {
public:
    int maxDepth(TreeNode* root) {
        if(!root) return 0;
        ::maxDepth = 0;
        findDepthTwo(root, 0);
        return ::maxDepth;

    }

    // Ref: https://walkccc.me/LeetCode/problems/104/
    int maxDepthThree(TreeNode* root) {
        if (!root) return 0;
        return 1 + max(maxDepthThree(root->left), maxDepthThree(root->right));
    }
};


int main() {
    vector< vector<int> > d1 = {
        {},
        {22},
        {3,9,20,-1,-1,15,7},
        {1,-1,2}
    };
    Solution s;
    for(auto a: d1) {
        auto root = makeTree(a);
        preOrderTraversal(root);
        
        cout << " Max Depth: " << s.maxDepthThree(root) << endl;
    }
    return 0;
}