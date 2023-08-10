/*
 * run: g++ list_0.cpp
 */

#include <iostream>
#include <list>
#include <cstdint>
#include <utility>

using namespace std;

void print(int id, const std::list<int>& container)
{
    std::cout << id << ". ";
    for (const int x: container)
        std::cout << x << ' ';
    std::cout << '\n';
}
 
int main() {
    list<int> ll;
    auto it = ll.begin();
    ll.insert(it,1);
    ll.insert(it,2);
    ll.insert(it,3);
    print(1, ll);
  
    it = std::prev(ll.end());
    cout << *(it) << endl;

    ll.erase(ll.begin());
    print(2, ll);
    // it is not invalidated even if first element is removed
    cout << *(it) << endl; 
    return 0;
}