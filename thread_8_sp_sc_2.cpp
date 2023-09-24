/*
 * run: g++ thread_8_sp_sc_2.cpp -lpthread -lboost_thread -lboost_chrono
 * Single Producer(sp), Single Consumer (sc) 
 *
 * Ref/Credits:
 * http://man.hubwiz.com/docset/Boost.docset/Contents/Resources/Documents/boost/doc/html/lockfree/examples.html
 * https://en.cppreference.com/w/cpp/chrono/duration/duration_cast
 * https://en.cppreference.com/w/cpp/chrono/high_resolution_clock/now
 * https://stackoverflow.com/questions/7560114/random-number-c-in-some-range/7560151
 *
 * What this program is doing?
 * ShmMsg is an object which producer is producing and putting it in a Q 
 * spsc_queue. consumer is consuming the ShmMsg object.
 * The requirement is consumer need to process objects in order strictly.
 * So as soon as producer puts the object in the Q, a thread from thread pool 
 * is attached to it and thread works on the work while ShmMsg object is 
 * traveling in the Q. consumer pull the object from Q only if thread has 
 * finished the work of ShmMsg object.
 */ 
 

#include <iostream>
#include <thread>
#include <boost/thread/thread.hpp>
#include <iostream>
#include <boost/atomic.hpp>
#include "ThreadPool.h"
#include <cstddef>
#include <chrono>
#include "RingBuffer.h"
#include <string>
#include <random>

using namespace std;

uint32_t totalTime = 0;
uint32_t maxTime = 0;
uint32_t minTime = 10000;

boostThread::ThreadPool *pool;

std::random_device rd; // obtain a random number from hardware
std::mt19937 gen(rd()); // seed the generator
std::uniform_int_distribution<> distr(1, 2000); // define the range

class ShmMsg {
    uint32_t msgNo;
    volatile bool done=false;
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
public: 
    ShmMsg(uint32_t no):msgNo(no) {
        start = std::chrono::high_resolution_clock::now();
        //cout << "Msg " << msgNo << " created!!!" << endl;
    };
    void processMsg() {
        
        boost::this_thread::sleep_for(boost::chrono::microseconds(distr(gen)));
        end = std::chrono::high_resolution_clock::now();
        done=true;
    }
    bool isDone() {return done;}
    void printTimeToProcess() {
        std::chrono::duration<double, std::milli> fp_ms = end - start;
        //cout << "Time taken to process " << msgNo << " is: " << fp_ms.count() << " ms" << std::endl; 
        //cout << fp_ms.count() << std::endl; 
        auto ticks = fp_ms.count();
        totalTime += ticks;
        if (maxTime < ticks) maxTime=ticks;
        if (minTime > ticks) minTime=ticks;
    }
};

int producer_count = 0;
boost::atomic_int consumer_count (0);

RingBuffer<ShmMsg*> *spsc_queue;

std::chrono::duration<double, std::milli> prodTime;

void producer(const uint32_t producerCount)
{
    pthread_setname_np(pthread_self(), __func__);
    auto t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i != producerCount; ++i) {
        int value = ++producer_count;
        ShmMsg *msg = new ShmMsg(value);
        while (!spsc_queue->getQ().push(msg)) {
            cout << "Producer Thread: Q full\n";
        }
        pool->service.post(
            boost::bind(&ShmMsg::processMsg, msg)
        );
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    prodTime = t2-t1;
}   

boost::atomic<bool> done (false);

void consumer(void)
{
    pthread_setname_np(pthread_self(), __func__);
    int value;
    ShmMsg* shmMsg = nullptr;
    while (!done) {
        while (spsc_queue->getQ().pop(shmMsg)){
            while(!shmMsg->isDone());
            shmMsg->printTimeToProcess();
            ++consumer_count;
        }
    }

    while (spsc_queue->getQ().pop(shmMsg)) {
        while(!shmMsg->isDone());
        shmMsg->printTimeToProcess();
        ++consumer_count;
    }
}

int main(int argc, char* argv[])
{
    if(4 != argc) {
        cout << "I expect 3 int args. Q_LENGHT PRODUCER_COUNT THREADS_IN_TP. " << endl;
        cout << "I trust you and I am not validating them" << endl;
        return -1;
    }
    uint32_t qSize = std::stoi(argv[1]);
    uint32_t producerCount = std::stoi(argv[2]);
    uint32_t thrdInTP = std::stoi(argv[3]);
    using namespace std;
    auto msgQ = new RingBuffer<ShmMsg*>(qSize); // capacity size: 3
    spsc_queue = msgQ;
    //std::cout << "Q Capacity is: " << spsc_queue->getQ().write_available() << std::endl;
    if (!spsc_queue->getQ().is_lock_free())
        cout << "boost::lockfree::queue is not lockfree" << endl;
    else
        cout << "boost::lockfree::queue is lockfree" << endl;

    pool = new boostThread::ThreadPool(thrdInTP);
    boost::thread producer_thread(producer, producerCount);
    boost::thread consumer_thread(consumer);

    producer_thread.join();
    done = true;
    consumer_thread.join();
    
    cout << "Q_LENGHT: " << qSize << endl;
    cout << "PRODUCER_COUNT: " << producerCount << endl;
    cout << "THREADS_IN_TP: " << thrdInTP << endl;
    cout << "min: " << minTime << " ms"  << endl;
    cout << "avg: " << totalTime/producerCount << " ms" << endl;
    cout << "max: " << maxTime << " ms" << endl;
    cout << "Producer Time: " << prodTime.count() << " ms" << endl;
    cout << "produced " << producer_count << " objects." << endl;
    cout << "consumed " << consumer_count << " objects." << endl;
    
    return 1;
}
 
