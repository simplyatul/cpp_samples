/*
 * run: g++ list_rotate_1.cpp
 * Vs list_rotate_0.cpp => using smart pointers
 * ToDo: Complete the rotate function
 */

#include <iostream>
#include <memory>

using namespace std;

// SLL - Singly Linked List
struct Node {
    shared_ptr<Node> next = nullptr;
    int k;
    ~Node() {
        cout << "D'tor: " << k << "\n";
    }
};

class SLL {
    shared_ptr<Node> head=nullptr;

public:
    void printLL() {
        shared_ptr<Node> temp = head;
        while(temp) {
            cout << temp->k << " ";
            temp = temp->next;
        }
        cout << "\n";
    }

    void addNode(const int d) {
        shared_ptr<Node> n = make_shared<Node>();
        n->k = d;
        n->next = head;
        head = n;
    }
#if 0
    void rotateLL(const uint32_t k) {
        if(!head /*no node at all*/ 
            || head->next /*only one node*/ == nullptr) {
            return;
        }

        Node* t = head;
        uint32_t n=1; // to compute # of nodes in SLL
        while(t->next) {
            t = t->next;
            n++;
        }
        t->next = head; // make the list circular
        auto shiftBy = n - (k%n);
        cout << "Shitfing By " << shiftBy << "\n";
        while(shiftBy--) {
            t = t->next;
        }
        // now t will point to new tail
        head = t->next;
        t->next = nullptr;
    }
#endif

};

int main() {
    SLL sll;
    sll.addNode(5);
    sll.addNode(4);
    sll.addNode(3);
    sll.addNode(2);
    sll.addNode(1);
    sll.printLL();

#if 0
    uint32_t rotateBy = 21;    
    sll.rotateLL(rotateBy);
    cout << "After Rotation by " << rotateBy << " places.\n";
    sll.printLL();
#endif
    return 0;
}