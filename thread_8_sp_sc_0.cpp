/*
 * run: g++ thread_8_sp_sc_0.cpp -lpthread -lboost_thread -lboost_chrono -lboost_date_time
 * Single Producer(sp), Single Consumer (sc) 
 *
 * Ref/Credits:
 * http://man.hubwiz.com/docset/Boost.docset/Contents/Resources/Documents/boost/doc/html/lockfree/examples.html
 * https://en.cppreference.com/w/cpp/chrono/duration/duration_cast
 * https://en.cppreference.com/w/cpp/chrono/high_resolution_clock/now
 */

#include <iostream>
#include <thread>
#include <boost/thread/thread.hpp>
#include <boost/lockfree/spsc_queue.hpp>
#include <iostream>
#include <boost/atomic.hpp>
#include "ThreadPool.h"
#include <cstddef>
#include <chrono>
//#include "common.h"

using namespace std;

#define Q_LENGHT        512
#define PRODUCER_COUNT  1000000
#define THREADS_IN_TP   16

uint32_t totalTime = 0;
uint32_t maxTime = 0;
uint32_t minTime = 0;

//ToDo: Name the Threadpool threads
boostThread::ThreadPool *pool;

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
        boost::this_thread::sleep_for(boost::chrono::milliseconds(1));
        end = std::chrono::high_resolution_clock::now();
        done=true;
    }
    bool isDone() {return done;}
    void printTimeToProcess() {
        std::chrono::duration<double, std::milli> fp_ms = end - start;
        //cout << "Time taken to process " << msgNo << " is: " << fp_ms.count() << " ms" << std::endl; 
        cout << fp_ms.count() << std::endl; 
        auto ticks = fp_ms.count();
        totalTime += ticks;
        if (maxTime < ticks) maxTime=ticks;
        if (minTime > ticks) minTime=ticks;
    }
};

int producer_count = 0;
boost::atomic_int consumer_count (0);

boost::lockfree::spsc_queue<ShmMsg*, boost::lockfree::capacity<Q_LENGHT> > spsc_queue;

const int iterations = PRODUCER_COUNT;

std::chrono::duration<double, std::milli> prodTime;

void producer(void)
{
    pthread_setname_np(pthread_self(), __func__);
    auto t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i != iterations; ++i) {
        int value = ++producer_count;
        ShmMsg *msg = new ShmMsg(value);
        pool->service.post(
            boost::bind(&ShmMsg::processMsg, msg)
        );
        while (!spsc_queue.push(msg))
            ;
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
        while (spsc_queue.pop(shmMsg)){
            while(!shmMsg->isDone());
            shmMsg->printTimeToProcess();
            ++consumer_count;
        }
    }

    while (spsc_queue.pop(shmMsg)) {
        while(!shmMsg->isDone());
        shmMsg->printTimeToProcess();
        ++consumer_count;
    }
}

int main(int argc, char* argv[])
{
    using namespace std;
    if (!spsc_queue.is_lock_free())
        cout << "boost::lockfree::queue is not lockfree" << endl;
    else
        cout << "boost::lockfree::queue is lockfree" << endl;

    pool = new boostThread::ThreadPool(THREADS_IN_TP);
    boost::thread producer_thread(producer);
    boost::thread consumer_thread(consumer);

    producer_thread.join();
    done = true;
    consumer_thread.join();
    
    cout << "Q_LENGHT: " << Q_LENGHT << endl;
    cout << "PRODUCER_COUNT: " << PRODUCER_COUNT << endl;
    cout << "THREADS_IN_TP: " << THREADS_IN_TP << endl;
    cout << "min: " << minTime << " ms"  << endl;
    cout << "avg: " << totalTime/PRODUCER_COUNT << " ms" << endl;
    cout << "max: " << maxTime << " ms" << endl;
    cout << "Producer Time: " << prodTime.count() << " ms" << endl;
    cout << "produced " << producer_count << " objects." << endl;
    cout << "consumed " << consumer_count << " objects." << endl;
}
 
