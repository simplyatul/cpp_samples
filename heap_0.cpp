#include <iostream>
#include <vector>
#include "sll_utils.h"
#include <bits/stdc++.h>

/*
 * Q: Merge k Sorted Lists
 * Ref: https://leetcode.com/problems/merge-k-sorted-lists/description/?envType=study-plan-v2&envId=top-interview-150
*/

using namespace std;

class Solution {
public:
    /*
     * https://walkccc.me/LeetCode/problems/23/#
     * This implementation manages pointers only 
     * next field in lists are updated
    */

    ListNode* mergeKListsTwo(vector<ListNode*>& lists) {
        ListNode dummy(0);
        ListNode* curr = &dummy;
        auto compare = [](ListNode* a, ListNode* b) { return a->val > b->val; };
        priority_queue<ListNode*, vector<ListNode*>, decltype(compare)> minHeap(
            compare);

        for (ListNode* list : lists)
        if (list != nullptr)
            minHeap.push(list);

        while (!minHeap.empty()) {
            ListNode* minNode = minHeap.top();
            minHeap.pop();
            if (minNode->next)
                minHeap.push(minNode->next);
            curr->next = minNode;
            curr = curr->next;
        }
        return dummy.next;
    }

    /*
     * This implementation takes integer value from lists
     * put it in minHeap
     * and created new LL
    */
    ListNode* mergeKLists(vector<ListNode*>& lists) {

        // create mean heap
        priority_queue<int, vector<int>,
                    greater<int>> minHeap;
        for(auto l: lists) {
            while(l) { 
                // cout << l->val << " ";
                minHeap.push(l->val);
                l = l->next;
            }
            // cout << "\n";
        }
        cout << "\n";
        
        ListNode dummy(0);
        ListNode* curr = &dummy;
        while (!minHeap.empty()) {
            // cout << pq.top() << " ";
            int k = minHeap.top();
            minHeap.pop();
            ListNode* node = new ListNode(k);
            curr->next = node;
            curr = curr->next;
        }

        return dummy.next;
    }
};

void makeKListOne(vector<ListNode*>& list) {
    ListNode *h1 = makeSLL({1,4,5});
    ListNode *h2 = makeSLL({1,3,4});
    ListNode *h3 = makeSLL({0,6});

    list.push_back(h1);
    list.push_back(h2);
    list.push_back(h3);
}


int main() {
    vector<ListNode*> list1;
    makeKListOne(list1);
    Solution s;
    ListNode* h = s.mergeKListsTwo(list1);
    printSLL(h);
    cout << "\n";
    return 0;
}