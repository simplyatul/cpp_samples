
#include "Timer.h"

void Timer::killThrd() {
    if (timerThrd.joinable()) {
        kill();
        timerThrd.join();
    }
    isKilled = false; //safe, because all threads are dead
    isReset = false;
}

auto Timer::lock() const {
    return std::unique_lock < std::mutex > (m);
}


void Timer::kill() {
    auto l = lock();
    isKilled = true;
    isReset = false;
    cv.notify_all();
}

void Timer::reset() {
    auto l = lock();
    isKilled = false;
    isReset = true;
    cv.notify_all();
}

Timer::~Timer() {
    killThrd();
}

void Timer::once(std::chrono::seconds sleep_duration) {
    killThrd();
    timerThrd = std::thread( [&] (std::chrono::seconds sd /*sleep duration*/) {
                auto l = lock();
                std::cout << "In Thread: " << std::this_thread::get_id() << std::endl;
                do {
                    isReset = false;
                    cv.wait_until(l, std::chrono::steady_clock::now() + sd, [&] { return isKilled or isReset; });
                    if (isKilled) return;
                } while (isReset);
                std::cout << "Existing Thread: " << std::this_thread::get_id() << std::endl;
            }, sleep_duration
        );
}

void Timer::once1(std::chrono::seconds sleep_duration, TimerCallback* cbk) {
    killThrd();
    timerThrd = std::thread( [&] (std::chrono::seconds sd /*sleep duration*/) {
                auto l = lock();
                std::cout << "In Thread: " << std::this_thread::get_id() << std::endl;
                do {
                    isReset = false;
                    cv.wait_until(l, std::chrono::steady_clock::now() + sd, [&] { return isKilled or isReset; });
                    if (isKilled) return;
                } while (isReset);
                std::cout << "Existing Thread: " << std::this_thread::get_id() << std::endl;
                cbk->onTimerExpire();
            }, sleep_duration
        );
}

void Timer::once2(std::chrono::seconds sleep_duration, std::shared_ptr<TimerCallback> cbk) {
    killThrd();
    timerThrd = std::thread( [&] (std::chrono::seconds sd /*sleep duration*/, std::shared_ptr<TimerCallback> cbk) {
                auto l = lock();
                std::cout << "once2: " << std::this_thread::get_id() << std::endl;
                do {
                    isReset = false;
                    cv.wait_until(l, std::chrono::steady_clock::now() + sd, [&] { return isKilled or isReset; });
                    if (isKilled) {
                        std::cout << "once2: Killed" << std::endl;
                        return;
                    }
                } while (isReset);
                std::cout << "Existing Thread: " << std::this_thread::get_id() << std::endl;
                cbk->onTimerExpire();
            }, sleep_duration, cbk
        );
}
