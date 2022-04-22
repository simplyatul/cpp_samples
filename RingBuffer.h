
#ifndef INCLUDE_RINGBUFFER_H_
#define INCLUDE_RINGBUFFER_H_

/*
 * This is just wrapper oever boost::lockfree::spsc_queue
 * so it can be initialized at the run time 
 * 
 * Ref/Credits:
 * https://stackoverflow.com/questions/57268969/how-to-pass-capacity-size-to-lock-free-spsc-queue-via-constructor
 */

#define USE_BOOST_SPSC_Q        
//#define USE_BOOST_LOCKFREE_Q    
//#define USE_STD_QUEUE_Q

#ifdef USE_BOOST_LOCKFREE_Q
#include <boost/lockfree/queue.hpp>
#endif

#ifdef USE_BOOST_SPSC_Q
#include <boost/lockfree/spsc_queue.hpp>
#endif

#include <iostream> 
#include <cstddef>

#define MIN_DEF_SIZE 2

template<class T>
class RingBuffer {
private:
    int capacity;
#ifdef USE_BOOST_LOCKFREE_Q
    boost::lockfree::queue<T> queue;
#endif

#ifdef USE_BOOST_SPSC_Q
    boost::lockfree::spsc_queue<T> queue;
#endif

public:
#ifdef USE_BOOST_LOCKFREE_Q
    boost::lockfree::queue<T> & getQ() {
#endif

#ifdef USE_BOOST_SPSC_Q
    boost::lockfree::spsc_queue<T> & getQ() {
#endif
        return queue;
    }

    int getCapacity(const uint32_t size) {
        if(size < MIN_DEF_SIZE){
            capacity = MIN_DEF_SIZE;
        } else {
            capacity = size;
        }
        return capacity;
    }

    explicit RingBuffer(const uint32_t size)
      : queue( getCapacity(size) )
    {
    
    }

    ~RingBuffer()
    = default;

};

#endif /* INCLUDE_RINGBUFFER_H_ */
