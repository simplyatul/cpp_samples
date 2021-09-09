/*
 * Cred/Ref: https://www.cppstories.com/2020/05/lambdas-async.html/
 */

#include <iostream>
#include <vector>
#include <thread>
#include <unistd.h>


int main() {
    int counter = 0;

    std::vector<std::thread> threads;
    for (int i = 0; i < 3; ++i) {
        threads.push_back(std::thread([&counter]() {
            std::cout << "In Thread: " << std::this_thread::get_id() << std::endl;
            for (int i = 0; i < 100; ++i) {
                ++counter;
                --counter;
                ++counter;
            }
            }));
    }

    for (auto& thread : threads) {
        thread.join();
    }

    std::cout << counter << std::endl;
    return 1;
}

