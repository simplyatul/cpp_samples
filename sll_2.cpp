#include <iostream>
#include <vector>
#include "sll_utils.h"

/*
 * Q: https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/description/
 * Remove Duplicates from Sorted List II
 * Given the head of a sorted linked list, delete all nodes that have duplicate 
 * numbers, leaving only distinct numbers from the original list.
 * Return the linked list sorted as well.
*/

using namespace std;

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        /*
         * Not working....
        */
        if(!head) return nullptr;
        ListNode* curr = head;
        ListNode* start = nullptr;
        ListNode* end = nullptr;
        ListNode* prev = head;
        bool skip = false;
        while(nullptr != curr && curr->next) {
            if(curr->val == curr->next->val) {
                if(!start) {
                    start = curr;
                    // find end
                    while(nullptr != curr && start->val == curr->val) {
                        end = curr;
                        curr = curr->next;
                        skip=true;
                    }
                    // point prev-next to curr
                    if(prev == start) {
                        head = curr;
                    } else {
                        prev->next = curr;
                    }
                    start = nullptr;
                }
            }
            prev = curr;
            if(skip) {
                skip=false;
                continue;
            }
            if(nullptr != curr)
                curr = curr->next;
        }
        return head;
    }
};

int main() {
    int n = 2;
    vector < vector<int> > input = {
        {4, 4, 6, 6, 6, 8, 9, 9, 10, 10},
        {4 ,4, 6, 6},
        {4,4},
        {1,2,2},
        {1,1,2},
        //{1,2,3,4,5}
        {1,2,2,3}
    };
    Solution s;
    for(auto i: input) {
        ListNode* head = makeSLL(i);
        cout << "In SLL:  ";
        printSLL(head);
        cout << endl;
        head = s.deleteDuplicates(head);
        cout << "Out SLL: ";
        printSLL(head);
        cout << endl;
    }
    return 0;
}