#include <iostream>
#include <vector>
#include <queue>
#include "tree_utils.h"
#include <unordered_map>


using namespace std;

// Q: Construct Binary Tree from Inorder and Postorder Traversal
// Q: https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/


class Solution {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        // map of values in inorder vector to it's index
        unordered_map<int, int> inOrderMap;
        for(auto i=0; i<inorder.size(); ++i) {
            inOrderMap[inorder[i]] = i;
        }

        TreeNode* root = buildTreeOne(
            inorder, 0, inorder.size()-1,
            postorder, 0, postorder.size()-1,
            inOrderMap
        );

        return root;
    }

    TreeNode* buildTreeOne(
        vector<int>& inorder, int iStartIdx, int iEndIdx,
        vector<int>& postorder, int pStartIdx, int pEndIdx,
        const unordered_map<int, int> &inOrderMap
    ) {
        auto it = inOrderMap.find(postorder[pEndIdx]);
        if(it == inOrderMap.end()) return nullptr;

        cout << "Elem Value: " << it->first << " Elem Index: " << it->second << endl;
        // found root of subtree
        auto root = new TreeNode(it->first);

        int iElemOnLeft = it->second - iStartIdx;
        int iElemOnRight = iEndIdx - it->second;

        if (iElemOnLeft > 0)
        {
            // build left subtree
            root->left = buildTreeOne(
                inorder, iStartIdx, it->second - 1,
                postorder, pStartIdx, pStartIdx + iElemOnLeft - 1,
                inOrderMap);
        }

        if (iElemOnRight > 0)
        {
            // build right subtree
            root->right = buildTreeOne(
                inorder, it->second + 1, iEndIdx,
                postorder, pStartIdx + iElemOnLeft, pEndIdx - 1,
                inOrderMap

            );
        }

        return root;
    }

};

struct inpost {
    vector<int> inorder;
    vector<int> postorder;
};

int main() {
    vector< inpost > d1 = {
        {{1,2,5}, {2,1,5}},
        {{9,3,15,20,7}, {9,15,7,20,3}},
        {{-1},{-1}}
    };
    Solution s;
    for(auto a: d1) {
        auto root = s.buildTree(a.inorder, a.postorder);
        postOrderTraversal(root); 
        cout << endl;
        


    }
    return 0;
}