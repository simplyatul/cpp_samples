/*
 * run: g++ thread_5.cpp -lboost_thread -lpthread
 */

#include <iostream>
#include <boost/thread/thread.hpp>
#include <unistd.h>
#include <sched.h>
#include <cstdio>
#include "common.h"

void* threadfunc()
{
    sleep(5);
}

void displayAndChange(boost::thread& daThread)
{
    int retcode;
    int policy;

    pthread_t threadID = (pthread_t) daThread.native_handle();

    struct sched_param param;

    if ((retcode = pthread_getschedparam(threadID, &policy, &param)) != 0)
    {
        errno = retcode;
        perror("pthread_getschedparam");
        exit(EXIT_FAILURE);
    }

    std::cout << "INHERITED: ";
    std::cout << "policy=" << ((policy == SCHED_FIFO)  ? "SCHED_FIFO" :
                               (policy == SCHED_RR)    ? "SCHED_RR" :
                               (policy == SCHED_OTHER) ? "SCHED_OTHER" :
                                                         "???")
              << ", priority=" << param.sched_priority << std::endl;


    policy = SCHED_FIFO;
    param.sched_priority = 4;

    if ((retcode = pthread_setschedparam(threadID, policy, &param)) != 0)
    {
        errno = retcode;
        perror("pthread_setschedparam");
        exit(EXIT_FAILURE);
    }

    std::cout << "  CHANGED: ";
    std::cout << "policy=" << ((policy == SCHED_FIFO)  ? "SCHED_FIFO" :
                               (policy == SCHED_RR)    ? "SCHED_RR" :
                               (policy == SCHED_OTHER) ? "SCHED_OTHER" :
                                                          "???")
              << ", priority=" << param.sched_priority << std::endl;
}


int main(int argc, char* argv[])
{
    int policy, res;

    struct sched_param param;

    if ((policy = sched_getscheduler(getpid())) == -1)
    {
        perror("sched_getscheduler");
        exit(EXIT_FAILURE);
    }

    if ((res = sched_getparam(getpid(), &param)) == -1)
    {
        perror("sched_getparam");
        exit(EXIT_FAILURE);
    }

    std::cout << " ORIGINAL: ";
    std::cout << "policy=" << ((policy == SCHED_FIFO)  ? "SCHED_FIFO" :
                               (policy == SCHED_RR)    ? "SCHED_RR" :
                               (policy == SCHED_OTHER) ? "SCHED_OTHER" :
                                                          "???")
              << ", priority=" << param.sched_priority << std::endl;


    policy = SCHED_RR;
    param.sched_priority = 2;

    if ((res = sched_setscheduler(getpid(), policy, &param)) == -1)
    {
        perror("sched_setscheduler");
        exit(EXIT_FAILURE);
    }

    boost::thread t1(&threadfunc);

    displayAndChange(t1);

    t1.join();

    return 0;
}

