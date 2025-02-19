#include <iostream>
#include <vector>
#include "sll_utils.h"

/*
 * Q: https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/description/
 * Remove Duplicates from Sorted List II
 * Given the head of a sorted linked list, delete all nodes that have duplicate 
 * numbers, leaving only distinct numbers from the original list.
 * Return the linked list sorted as well.
 * 
 * Input 1 2 2 3
 * Output 1 3
 * 
 * Ref: https://walkccc.me/LeetCode/problems/82/#__tabbed_1_1
*/

using namespace std;

class Solution {
public:
    // Q: https://leetcode.com/problems/remove-duplicates-from-sorted-list/description/
    // deletes all duplicates except one
    ListNode *deleteDuplicatesOne(ListNode *head) {
        ListNode dummy(0, head);
        ListNode *prev = head;
        bool movePrev = true;
        while (head != nullptr) {
            while (head->next && head->val == head->next->val) {
                head = head->next;
            }
            if(head != prev) {
                prev->next = head->next;
                prev = head->next;
            }
            head = head->next;
            prev = head;
        }
        return dummy.next;
    }

    // deletes all duplicates
    ListNode *deleteDuplicatesTwo(ListNode *head)
    {
        ListNode dummy(0, head);
        ListNode *prev = &dummy;

        while (head != nullptr)
        {
            while (head->next && head->val == head->next->val)
                head = head->next;
            if (prev->next == head)
                prev = prev->next;
            else
                prev->next = head->next;
            head = head->next;
        }

        return dummy.next;
    }
};

int main() {
    int n = 2;
    vector < vector<int> > input = {
        {1,2,2,3},
        {1,1,2},
        {4, 4, 6, 6, 6, 8, 9, 9, 10, 10},
        {4 ,4, 6, 6},
        {4,4},
        {1,2,2},
        //{1,2,3,4,5}
        {1,2,2,3},
        {-1, 0, 1,2,3,4}
    };
    Solution s;
    for(auto i: input) {
        ListNode* head = makeSLL(i);
        cout << "In SLL:  ";
        printSLL(head);
        cout << endl;
        head = s.deleteDuplicatesOne(head);
        cout << "Out SLL: ";
        printSLL(head);
        cout << endl;
    }
    return 0;
}