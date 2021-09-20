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

#include "TimerCallback.h"

class Timer {
    std::condition_variable cv;
    mutable std::mutex m;
    bool isKilled = false;
    bool isReset = false;
    std::thread timerThrd;

    void killThrd();

    auto lock() const;

public:
    void kill();
    void reset() ;
    ~Timer();
    void once(std::chrono::seconds sleep_duration);
    void once1(std::chrono::seconds sleep_duration, TimerCallback* cbk);
    void once2(std::chrono::seconds sleep_duration, std::shared_ptr<TimerCallback> cbk);
};


#endif /* INCLUDE_TIMER_H_ */
