#ifndef TIMER_H
#define TIMER_H

#include <thread>
#include <chrono>
#include <atomic>
#include <condition_variable>
#include <mutex>
#include <iostream>

class Timer {
    std::condition_variable cv;
    mutable std::mutex m;
    bool isKilled = false;
    bool isReset = false;
    std::thread active_thread;


    void dispose_thread() {
        if (active_thread.joinable()) {
            kill();
            active_thread.join();
        }
        isKilled = false; //safe, because all threads are dead
        isReset = false;
    }

    auto lock() const {
        return std::unique_lock(m);
    }

public:
    [[maybe_unused]] void kill() {
        auto l = lock();
        isKilled = true;
        isReset = false;
        cv.notify_all();
    }

    [[maybe_unused]] void reset() {
        auto l = lock();
        isKilled = false;
        isReset = true;
        cv.notify_all();
    }

    ~Timer() { dispose_thread(); }

    template<class Function, class... Args, class Rep, class Period>
    [[maybe_unused]] void once(std::chrono::duration<Rep, Period> sleep_duration, Function &&f, Args &&... args);

    template<class Function, class... Args, class Rep, class Period>
    [[maybe_unused]] void
    repeat(std::chrono::duration<Rep, Period> sleep_duration, Function &&f, Args &&... args);
};

template<class Function, class... Args, class Rep, class Period>
void Timer::once(std::chrono::duration<Rep, Period> sleep_duration, Function &&f, Args &&... args) {
    dispose_thread();
    active_thread = std::thread(
            [&, sleep_duration, f = std::forward<Function>(f), args = std::make_tuple(std::forward<Args>(args)...)]() {
                auto l = lock();
                do {
                    isReset = false;
                    cv.wait_until(l, std::chrono::steady_clock::now() + sleep_duration, [&] { return isKilled or isReset; });
                    if (isKilled) return;
                } while (isReset);

                std::apply(f, args);
            });
}

template<class Function, class... Args, class Rep, class Period>
void Timer::repeat(std::chrono::duration<Rep, Period> sleep_duration, Function &&f, Args &&... args) {
    dispose_thread();
    active_thread = std::thread(
            [&, sleep_duration, f = std::forward<Function>(f), args = std::make_tuple(std::forward<Args>(args)...)]() {
                while (true) {
                    auto l = lock();
                    do {
                        isReset = false;
                        cv.wait_until(l, std::chrono::steady_clock::now() + sleep_duration, [&] { return isKilled or isReset; });
                        if (isKilled) return;
                    } while (isReset);
                    std::apply(f, args);
                }
            });
}

#endif
