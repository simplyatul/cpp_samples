/*
 * utils.h
 *
 */

#ifndef INCLUDE_UTILS_H_
#define INCLUDE_UTILS_H_

using namespace std;

#include <iostream>
#define cout \
    cout << std::time(nullptr) << ": " << __FILENAME__ << ":" << __func__ << ":" << __LINE__ << ": "

#endif /* INCLUDE_UTILS_H_ */
