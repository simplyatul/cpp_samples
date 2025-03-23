#include <iostream>
#include <vector>
#include <queue>
#include <bits/stdc++.h>
#include "tree_utils.h"
#include <unordered_map>


using namespace std;

/*
 * Q:  Subtree of Another Tree
 * Ref: 572 - https://leetcode.com/problems/subtree-of-another-tree/description/
 */

class Solution {
public:
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        // ToDo => find subRoot in root

        // check if equal

        return isEqual(root, subRoot);
    }

    TreeNode* findSubRoot(TreeNode* root, TreeNode* subRoot) {
        if(!root) return nullptr;
        if(root->val == subRoot->val)
            return root;
        if (findSubRoot(root->left, subRoot))
    }

    bool isEqual(TreeNode* t1, TreeNode* t2) {
        if (!t1 && !t2) return true;
        if (!t1 || !t2) return false;
        if(t1->val == t2->val) {
            bool isLeftSubTreeEqual = isEqual(t1->left, t2->left);
            bool isRightSubTreeEqual = isEqual(t1->right, t2->right);
            return isLeftSubTreeEqual == isRightSubTreeEqual == 1;
        }
        return false;
    }
};

int main() {
    Solution s;
    vector<int> t1 = {3,4,5,1,2,-1,-1,-1,-1,0};
    TreeNode *root = makeTree(t1);
    printLevelOrderTraversal(root);
    cout << endl << endl;

    vector<int> t2 = {4,1,2};
    TreeNode *subroot = makeTree(t2);
    printLevelOrderTraversal(subroot);
    cout << endl << endl;

    cout << "Is subtree: " << s.isSubtree(root->left, subroot);

    cout << endl << endl;
    return 0;
}