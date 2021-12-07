/*
 * run: g++ thread_6.cpp -lboost_thread -lpthread
 *
 * load a thread using CPU intesive task
 * Give a name a boost thread
 * Watch on the process and thread 
 * ps -o pid,tid,%cpu,cputimes,%mem,rss,vsz,ni,comm,cmd -L `pgrep a.out`
 */

#define ONE_MB (1*1024*1024)

#include <iostream>
#include <boost/thread.hpp>
#include "common.h"
#include <sys/types.h>
#include <stdlib.h>

void newThrd() {
    cout << "In newThrd " << gettid() << endl;
 
    // following op loads the CPU 70-99%
    float n = 1.5;
    while(true) {
        n*=n;
    }
}

void newThrd_1() {
    
    cout << "In " << __func__ << endl;
    
    pthread_t currThrd = pthread_self();
    pthread_t tId = pthread_self();
    cout << "TID: " << to_string(tId) << endl;
    pthread_setname_np(currThrd, __func__);
    sleep(500);
}

void doThrd(std::string name) {
    cout << "In doThrd " << name << endl;
    boost::thread t2(newThrd);
#if  defined(BOOST_THREAD_PLATFORM_PTHREAD)
        pthread_setname_np(t2.native_handle(), "newThrd");
#endif
    while(true) {
        char* c = (char*) calloc(sizeof(char), ONE_MB*50);
        sleep(1);
    }
}

int main() {
    cout << "Main Thread Id: " << boost::this_thread::get_id() << " And TId is : " << gettid() << endl;
    boost::thread t1(doThrd, "T1");

#if  defined(BOOST_THREAD_PLATFORM_PTHREAD)
        pthread_setname_np(t1.native_handle(), "doThrd");
#endif

    boost::thread t2(newThrd_1);

    t1.join();

    return 0;
}
