/*
 * Timer.h
  */

#ifndef INCLUDE_TIMER_H_
#define INCLUDE_TIMER_H_

#include "utils.h"
#include <thread>
#include <chrono>
#include <atomic>
#include <condition_variable>
#include <mutex>
#include <iostream>
#include "Callback.h"

class Timer {
    std::condition_variable cv;
    mutable std::mutex m;
    bool isKilled = false;
    bool isReset = false;
    std::thread active_thread;

    void killThrd();

    auto lock() const;

public:
    void kill();
    void reset() ;
    ~Timer();
    void once(std::chrono::seconds sleep_duration);
    void once1(std::chrono::seconds sleep_duration, Callback* cbk);
    void once2(std::chrono::seconds sleep_duration, std::shared_ptr<Callback> cbk);
};



#endif /* INCLUDE_TIMER_H_ */
