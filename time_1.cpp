
/*
 * run: g++ time_1.cpp -lpthread
 * localtime is not thread safe and hence Min and Sec values 
 * will change in T1 thread even if T1 does not call get_local_time
 */

#include <string>
#include <iostream>
#include <memory>
#include <cstring>
#include <unistd.h>
#include <time.h>
#include <thread>

static tm *get_local_time() {
    time_t currentTime;
    time(&currentTime);

    struct tm *localTime;
    localTime = localtime(&currentTime);

    return localTime;
}

void T1() {
    tm *time =get_local_time();
    while(true) {
        std::cout << "T1 -> Min: " << time->tm_min << " Sec: " << time->tm_sec << std::endl;
        sleep(1);
    }
}

void T2() {
    while(true) {
        tm *time =get_local_time();
        sleep(1);
    }
}

int main() {

    /*
    tm *time =get_local_time();
    while(true) {
        std::cout << "Min: " << time->tm_min << " Sec: " << time->tm_sec << std::endl;
        sleep(1);
    }
    */

    const std::time_t now = std::time(nullptr) ; // get the current time point
    const std::tm calendar_time = *std::localtime( std::addressof(now) ) ;

    std::cout << "Sec: " << calendar_time.tm_sec << std::endl;

    std::thread t1(T1);
    std::thread t2(T2);
    t1.join();
    t2.join();
    return 0;
}
