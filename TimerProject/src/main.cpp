/*
 * main.cpp
 *
 */

#include "utils.h"
#include "Timer.h"
#include "TimerUser.h"
#include <unistd.h>

int main() {
#if 0
    std::cout << std::endl << "--------- Scenario #0-----------" << std::endl;
    TimerUser tu1;
    tu1.setTimer(std::chrono::seconds(1));
    /*
     * Above thows run time error
     * terminate called after throwing an instance of 'std::bad_weak_ptr'
     *
     * This is bec TimerUser class derived from std::enable_shared_from_this need
     * to be managed by Shared pointer only.
     * Ref/Cred: https://stackoverflow.com/questions/5558734/c-bad-weak-ptr-error
     */
    std::cout << "Sleeping..." << std::endl;
    sleep(2);
    //TimerUser tu2 = tu1; // error: use of deleted function ‘TimerUser::TimerUser(const TimerUser&)’
    // This is because std::thread from Timer class is not CopyConstructible or CopyAssignable
    // Also, std::mutex is neither copyable nor movable

#endif

    std::cout << std::endl << "--------- Scenario #1-----------" << std::endl;
    Timer t1;
    std::shared_ptr <TimerCallback> cbk = std::make_shared<TimerUser> ();
    t1.once2(std::chrono::seconds(1), cbk);
    std::cout << "Sleeping..." << std::endl;
    sleep(2);

    std::cout << std::endl << "--------- Scenario #2-----------" << std::endl;
    std::shared_ptr <TimerUser> timerUser = std::make_shared<TimerUser> ();
    timerUser->setTimer(std::chrono::seconds(1));
    std::cout << "Sleeping..." << std::endl;
    sleep(3);

    std::cout << std::endl << "--------- Scenario #3-----------" << std::endl;
    std::shared_ptr <TimerUser> timerUser1 = std::make_shared<TimerUser> ();
    timerUser1->setTimer(std::chrono::seconds(10));
    std::cout << "Sleeping..." << std::endl;
    sleep(1);
    timerUser1->killTimer();
    sleep(1);

    return 0;
}
