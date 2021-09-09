#include <thread>
#include <chrono>
#include <atomic>
#include <condition_variable>
#include <mutex>
#include <iostream>
#include <unistd.h>

#define cout \
    cout << std::time(nullptr) << ": " << __func__ << ":" << __LINE__ << ": "

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
#if 1
    auto lock() const {
        return std::unique_lock<std::mutex> (m);
    }
#endif

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

#if 0
    template<class Function, class... Args, class Rep, class Period>
    [[maybe_unused]] void once(std::chrono::duration<Rep, Period> sleep_duration, Function &&f, Args &&... args);

    template<class Function, class... Args, class Rep, class Period>
    [[maybe_unused]] void
    repeat(std::chrono::duration<Rep, Period> sleep_duration, Function &&f, Args &&... args);
#endif

    ~Timer() { dispose_thread(); }
    
    void once(std::chrono::seconds sleep_duration) {
        dispose_thread();
        active_thread = std::thread( [&] (std::chrono::seconds sd) {
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

};

#if 0
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

class Wrapper {
    Timer t1;
public:
    void callTimer() {
        
    }
};

int main() {
    Timer t1;
    t1.once(std::chrono::seconds(1));
    std::cout << "Sleeping..." << std::endl;
    sleep(3);
    return 0;
}

