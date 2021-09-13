/*
 * main.cpp
 *
 */

#include "utils.h"
#include "Timer.h"
#include "TimerUser.h"
#include <unistd.h>

int main() {
    std::cout << std::endl << "--------- Scenario #1-----------" << std::endl;
    Timer t1;
    std::shared_ptr <Callback> cbk = std::make_shared<TimerUser> ();
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
