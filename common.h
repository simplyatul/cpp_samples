/*
 * common.h
 *
 */

#ifndef INCLUDE_COMMON_H_
#define INCLUDE_COMMON_H_

using namespace std;

#include <iostream>
#include <ctime>
#include <thread>
#include <chrono>

#define cout \
    cout << std::time(nullptr) << ": "      \
        << this_thread::get_id() << ": "    \
        << __FILE__ << ":"                  \
        << __func__ << ":"                  \
        << __LINE__ << ": "

#define GET_CURR_TIME chrono::high_resolution_clock::now()
#define START_TIME(s) auto s = GET_CURR_TIME
#define STOP_TIME(e) auto e = GET_CURR_TIME
#define DIFF_IN_MS(s,e) chrono::duration<double, std::milli>(e-s).count()

#endif /* INCLUDE_COMMON_H_ */
