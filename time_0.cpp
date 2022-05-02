/*
 * run: g++ time_0.cpp
 */
#include "common.h"
#include <cstdint>
#include <chrono>
#include <unistd.h>

#define MILLI_SEC_FACTOR    1000000
int main(int argc, char *argv[])
{
    std::chrono::nanoseconds totalTime = std::chrono::nanoseconds(0);
    std::chrono::nanoseconds maxTime = std::chrono::nanoseconds(609683525);
    std::chrono::nanoseconds minTime = std::chrono::nanoseconds( std::chrono::milliseconds(100) );
    uint64_t totalMsgsProcessed = 0;

    cout << "minTime: " << to_string(minTime.count()/MILLI_SEC_FACTOR) << " ms" << endl;
    cout << "totalTime: " << to_string(totalTime.count()) << endl;
    cout << "maxTime: " << to_string(maxTime.count()/MILLI_SEC_FACTOR) << " ms" << endl;
    auto avg = totalTime.count() / (totalMsgsProcessed?totalMsgsProcessed:1); 
    cout << "avg: " << to_string(avg) << endl;
    std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
    sleep(1);
    std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();
    auto diff = end - start;
    cout << "Type of Diff " << typeid(diff).name() << endl; // prints the cryptic type name 
    // void *a = diff;
    /* Above throws following error by which one can identify
     * the type of diff
     * 
     * error: cannot convert ‘std::chrono::duration<long int, std::ratio<1, 1000000000> >’ to ‘void*’ in initialization
      |     void *a = diff;
      |               ^~~~
      |               |
      |               std::chrono::duration<long int, std::ratio<1, 1000000000> >
     * 
     */
    cout << "Diff " << to_string(diff.count()) << " ns" << endl;
    return 0;
}


