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

TreeNode* makeTree_One() {
    /*
                    3
                 /      \
             9           20
                        /   \
                      15     7
    */
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


TreeNode* makeTree_Three() {
    TreeNode* l100 = new TreeNode(100);
    TreeNode* l250 = new TreeNode(250);
    TreeNode* l500 = new TreeNode(500);
    TreeNode* i200 = new TreeNode(200, l100, l250);
    TreeNode* i400 = new TreeNode(400, nullptr, l500);

    TreeNode* r300 = new TreeNode(300, i200, i400);
    return r300;
}

vector<int> MorrisInOrderTraversal(TreeNode* root) {
    vector<int> ans;
    TreeNode* curr = root;
    while(curr != nullptr) {
        if(curr->left != nullptr) { // left subtree exists
            // find curr's inorder predecessor
            TreeNode* prev = curr->left;
            while(prev->right != nullptr && 
                    prev->right != curr) {
                prev = prev->right;
            }
            // prev points to inorder predecessor
            if(prev->right == nullptr) {
                // point prev (predecessor) to curr (successor)
                prev->right = curr;
                curr = curr->left;
            } else {
                // revert the changes made above
                prev->right = nullptr;
                ans.push_back(curr->val);
                cout << curr->val << " ";
                curr = curr->right;
            }
        } else { // no left subtree
            ans.push_back(curr->val);
            cout << curr->val << " ";
            curr = curr->right;
        }
    }
    return ans;
}

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

vector<vector<int>> levelOrderTraversal(TreeNode* root) {
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

void printLevelOrderTraversal(TreeNode* root) {
    auto lo = levelOrderTraversal(root);
    for(auto v: lo) {
        for(auto i: v) {
            cout << i << " ";
        }
        cout << endl;
    }

}

#endif // end of __TREE_UTILS_H__
