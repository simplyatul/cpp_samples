#ifndef __TREE_UTILS_H__
#define __TREE_UTILS_H__ 1
#include <iostream>
using namespace std;

struct TreeNode
{
    int h = -1; // dist from root.
    int val;
    
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

void inOrderTraversal(const TreeNode* root) {
    if(!root) return;
    inOrderTraversal(root->left);
    cout << root->val << " ";
    inOrderTraversal(root->right);
};

void preOrderTraversal(const TreeNode* root) {
    if(!root) return;
    cout << root->val << " ";
    preOrderTraversal(root->left);
    preOrderTraversal(root->right);
};

void postOrderTraversal(const TreeNode* root) {
    if(!root) return;
    postOrderTraversal(root->left);
    postOrderTraversal(root->right);
    cout << root->val << " ";
};

#endif // end of __TREE_UTILS_H__
