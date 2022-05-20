/*
 * run: g++ cv_0.cpp -lpthread
 * Demonstrate usage of condition variable
 */

#include <iostream>
#include <atomic>
#include <condition_variable>
#include <thread>
#include <chrono>
using namespace std::chrono_literals;
 
std::condition_variable cv;
std::mutex cv_m;
std::atomic<int> i{0};
 
void waitThread(const int ms)
{
    std::unique_lock<std::mutex> lk(cv_m);
    auto now = std::chrono::system_clock::now();
    if(cv.wait_until(lk, now + ms*1ms, [](){return i == 1;})) {
        /*
         * True => i set to 1
         */
        std::cout << "Thread " << ms << " Condition becomes true. i == " << i << '\n';
    } else {
        /*
         * False => 
         * thread has timed out, finished waiting. i remains 0
         * Or
         * thread is notified (via cv.notify_all())
         */
        std::cout << "Thread " << ms << " Timed cout or Notified. i == " << i << '\n';
    }
}
 
void signalThread(const int signalAfterInms)
{
    std::this_thread::sleep_for(signalAfterInms*1ms);
    i = 1;
//    std::cout << "Notifying...\n";
//    cv.notify_all();
}
 
int main()
{
    std::thread 
        t1(waitThread, 200), 
        t2(waitThread, 400), 
        t3(waitThread, 1000), 
        t4(signalThread, 100);
    t1.join(); 
    t2.join();
    t3.join();
    t4.join();
}
