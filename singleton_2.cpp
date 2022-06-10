/*
 * run: g++ singleton_2.cpp
 * Compared to singleton_1.cpp, Logger instance is created before main
 * starts
 */


#include <iostream>
#include <unistd.h>

class Logger
{
private:
    Logger() {
        std::cout << "In C'tor" << std::endl;
    };
    Logger(const Logger&) = delete ;
    Logger & operator=(const Logger&) = delete;

public:
    static Logger  m_instance;

    static Logger & Instance() {
        return m_instance;
    }

    void log() {
        std::cout << "In log: " << this << std::endl;
    }

    ~Logger() = default;
};

Logger Logger::m_instance;

int main()
{
    std::cout << "In main " << std::endl;
    sleep(2);
    Logger &lg0 = Logger::Instance(); // This is only allowed
    lg0.log();
    Logger &lg00 = Logger::Instance();
    lg00.log();
    return 0;
}

/*
 * Output
    In C'tor
    In main
    In log: 0x557892af3151
    In log: 0x557892af3151
 */

