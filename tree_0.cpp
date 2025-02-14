#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Q: Given the root of a binary tree, return its maximum depth
// Q: https://leetcode.com/problems/maximum-depth-of-binary-tree/description/

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

TreeNode* makeTree(const vector<int> &nodes) {
    if(nodes.empty() || nodes[0] == -1) return NULL;

    TreeNode* root = new TreeNode(nodes[0]);
    queue<TreeNode*> q;
    q.push(root);
    int i = 1;
    while(!q.empty() && i < nodes.size()) {
        TreeNode* curr = q.front();
        q.pop();

        // left child
        if(i < nodes.size() && nodes[i] != -1) {
            TreeNode* left = new TreeNode(nodes[i]);
            curr->left = left;
            q.push(left);
        }
        i++;

        if(i < nodes.size() && nodes[i] != -1) {
            TreeNode* right = new TreeNode(nodes[i]);
            curr->right = right;
            q.push(right);
        }
        i++;
    }

    return root;

}

void inOrderTravarsal(const TreeNode* root) {
    if(!root) return;
    inOrderTravarsal(root->left);
    cout << root->val << " ";
    inOrderTravarsal(root->right);
};

void preOrderTravarsal(const TreeNode* root) {
    if(!root) return;
    cout << root->val << " ";
    preOrderTravarsal(root->left);
    preOrderTravarsal(root->right);
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
        preOrderTravarsal(root);
        
        cout << " Max Depth: " << s.maxDepthThree(root) << endl;
    }
    return 0;
}