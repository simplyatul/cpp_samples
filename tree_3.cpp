#include <iostream>
#include <vector>
#include <queue>
#include <bits/stdc++.h>
#include "tree_utils.h"
#include <unordered_map>


using namespace std;

/*
 * Q: 
 * 
 */

class Solution {
public:
    TreeNode* reverseOddLevels(TreeNode* root) {
        if(!root) return nullptr;
        if(root->left && root->right)
            rol(root->left, root->right, 1);
        return root;
    }

    void rol(TreeNode* lf, TreeNode* rt, int height) {
        if(!lf || !rt) return;
        if(height % 2 != 0) {
            swap(lf->val, rt->val);
        }
        if(lf->left && rt->right)
            rol(lf->left, rt->right, height+1);
        if(lf->right && rt->left)
            rol(lf->right, rt->left, height+1);
    }
};


int main() {
    Solution s;
    vector<int> t1 = {2,3,5,8,13,21,34,2,1,3,4,7,11,29,18};
    TreeNode *root = makeTree(t1);
    printLevelOrderTraversal(root);
    cout << endl << endl;
    s.reverseOddLevels(root);
    cout << "LevelOrderTraversal post reverseOddLevels" << endl;
    printLevelOrderTraversal(root);
    cout << endl << endl;
    return 0;
}