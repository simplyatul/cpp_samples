#ifndef __SLL_UTILS_H__
#define __SLL_UTILS_H__ 1

#include <iostream>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

void printSLL(const ListNode *head) {
    while(head) {
        cout << head->val << " ";
        head=head->next;
    }
}

ListNode* makeSLL(const vector<int> &in) {
    if(! in.size()) return nullptr;
    ListNode* dummy = new ListNode();
    ListNode* head = nullptr;
    for(auto i=0; i < in.size(); ++i) {
        ListNode* node = new ListNode(in[i]);
        if(!head) {
            head = node;
            dummy->next = head;
        } else {
            head->next = node;
            head = node;
        }
    }
    
    return dummy->next;
}

#endif // end of __SLL_UTILS_H__