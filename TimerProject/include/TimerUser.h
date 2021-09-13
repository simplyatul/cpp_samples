/*
 * TimerUser.h
 *
 */

#ifndef INCLUDE_TIMERUSER_H_
#define INCLUDE_TIMERUSER_H_

#include "utils.h"
#include "Timer.h"
#include "Callback.h"

class TimerUser : public Callback, public std::enable_shared_from_this<TimerUser> {
    Timer noRes;
public:
    void onTimerExpire() {
        std::cout << "TimerUser::In onTimerExpire" << std::endl;
    };

    void killTimer() {
        std::cout << "Killing Timer" << std::endl;
        noRes.kill();
    }

    void setTimer(std::chrono::seconds s) {
        noRes.once2(s, shared_from_this());
    }

};



#endif /* INCLUDE_TIMERUSER_H_ */
