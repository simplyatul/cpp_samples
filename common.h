/*
 * common.h
 *
 */

#ifndef INCLUDE_COMMON_H_
#define INCLUDE_COMMON_H_

using namespace std;

#include <iostream>
#include <ctime>

#define cout \
    cout << std::time(nullptr) << ": " << __FILE__ << ":" << __func__ << ":" << __LINE__ << ": "

#endif /* INCLUDE_COMMON_H_ */
