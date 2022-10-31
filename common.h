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

#define cout \
    cout << std::time(nullptr) << ": "      \
        << this_thread::get_id() << ": "    \
        << __FILE__ << ":"                  \
        << __func__ << ":"                  \
        << __LINE__ << ": "

#endif /* INCLUDE_COMMON_H_ */
