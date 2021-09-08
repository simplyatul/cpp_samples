#include <boost/lockfree/queue.hpp>
#include <iostream>

int main() {
    
    boost::lockfree::queue<int*> spiMsgQ{1000};	
    int *k = new int(0);
    int *k1 = new int(1);
    
    spiMsgQ.push(k);
    spiMsgQ.push(k1);
    

    int *ptr;
    spiMsgQ.pop(ptr);
    std::cout << *ptr << std::endl;
    spiMsgQ.pop(ptr);
    std::cout << *ptr << std::endl;
    return 0;
}
