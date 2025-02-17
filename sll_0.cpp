#include <iostream>
#include <vector>
#include "sll_utils.h"

/*
 * Q: https://leetcode.com/problems/remove-nth-node-from-end-of-list/description/
 * Remove Nth Node From End of List
*/
using namespace std;

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if(!head) return nullptr;
        ListNode* prev = head;
        ListNode* next = head;
        int incBy = n;
        while(incBy>0 && next) {
            next = next->next;
            incBy--;
        }
        if(!next) {
            return head->next;
        }

        while(next->next != nullptr) {
            prev = prev->next;
            next=next->next;
        }

        prev->next = prev->next->next;
        return head;
    }
};

int main() {
    int n = 2;
    vector < vector<int> > input = {
        //{1,2,3,4,5}
        {1,2}
    };
    Solution s;
    for(auto i: input) {
        ListNode* head = makeSLL(i);
        printSLL(head);
        cout << endl;
        head = s.removeNthFromEnd(head, n);
        printSLL(head);
        cout << endl;
    }
    return 0;
}