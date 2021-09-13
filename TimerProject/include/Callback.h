/*
 * Callback.h
 *
 */

#ifndef INCLUDE_CALLBACK_H_
#define INCLUDE_CALLBACK_H_

#include "utils.h"

class Callback {
public:
    virtual void onTimerExpire() = 0;
};



#endif /* INCLUDE_CALLBACK_H_ */
