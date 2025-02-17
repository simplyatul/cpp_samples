#include <iostream>
#include <vector>
#include "sll_utils.h"

/*
 * Q: https://leetcode.com/problems/swapping-nodes-in-a-linked-list/description/
 * Swapping Nodes in a Linked List
*/
using namespace std;

class Solution {
public:
    ListNode* swapNodes(ListNode* head, int k) {
        if(!head) return nullptr;
        // nodes to be swapped
        ListNode* one = head;
        ListNode* two = head;

        int kk = k-1;
        int totalNodes = 1;
        // inc one by k nodes, count total nodes
        // one will be positioned to a node to be swapped
        while(kk-- > 0) {
            one=one->next;
            totalNodes++;
        }

        two=one;
        while(two->next) {
            totalNodes++;
            two=two->next;
        }

        // position two to next node t be swapped
        two=head;
        int incBy = totalNodes - k;
        while(incBy--) {
            two = two->next;
        }

        swap(one->val, two->val);
        return head;
    }
};

int main() {
    int k = 3;
    vector < vector<int> > input = {
        {1, 2, 3}
    };
    Solution s;
    for(auto i: input) {
        ListNode* head = makeSLL(i);
        printSLL(head);
        cout << endl;
        head = s.swapNodes(head, k);
        printSLL(head);
        cout << endl;
    }
    return 0;
}