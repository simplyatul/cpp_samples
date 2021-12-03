/*
 * run: g++ thread_8_sp_sc_1.cpp -lpthread -lboost_thread -lboost_chrono -lboost_date_time
 * Single Producer(sp), Single Consumer (sc)
 * Wrap Boost spsc_queue in Template so as to accept capacity at runtime 
 *
 * Ref/Credits:
 * https://stackoverflow.com/questions/57268969/how-to-pass-capacity-size-to-lock-free-spsc-queue-via-constructor
 */


#include <boost/lockfree/spsc_queue.hpp>
#include <iostream> 

template<class T>
class RingBuffer {
private:
    int capacity;
    boost::lockfree::spsc_queue<T> queue;

public:
    boost::lockfree::spsc_queue<T> & getRingBufferObj() {
        return queue;
    }

    int getCapacity(int size) {
        if(size < 2){
            capacity = 2;
        } else {
            capacity = size;
        }
        return capacity;
    }

    explicit RingBuffer(int size)
      : queue( getCapacity(size) )
    {
    
    }

    ~RingBuffer()
    = default;

    int Insert(); // queue.push()
    int Extract(); // queue.pop()
};

int main(int argc, char *argv[]) {

    auto ringBuffer = new RingBuffer<int>(3); // capacity size: 3
    std::cout << "Type: " <<  typeid(ringBuffer).name() << std::endl;
    std::cout << "Capacity: " << ringBuffer->getRingBufferObj().write_available() << std::endl;
    ringBuffer->getRingBufferObj().push(1);
    ringBuffer->getRingBufferObj().push(2);
    ringBuffer->getRingBufferObj().push(3);
    std::cout << "Capacity: " << ringBuffer->getRingBufferObj().write_available() << std::endl;

    int v;
    ringBuffer->getRingBufferObj().pop(v);
    std::cout << v << std::endl;
    std::cout << "Capacity: " << ringBuffer->getRingBufferObj().write_available() << std::endl;

    delete ringBuffer;
    return 0;
}

