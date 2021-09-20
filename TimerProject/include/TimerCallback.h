/*
 * TimerCallback.h
 *
 */

#ifndef INCLUDE_TIMERCALLBACK_H_
#define INCLUDE_TIMERCALLBACK_H_

#include "utils.h"

class TimerCallback {
public:
    virtual void onTimerExpire() = 0;
};



#endif /* INCLUDE_TIMERCALLBACK_H_ */
