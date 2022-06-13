/*
 * run: g++ singleton_4.cpp -lpthread
 * Curiously Recurring Template Pattern (CRTP)
 *  Template Base Class is inherited in child class
 *  and the singular behavior is inherited in child class
 */


#include <iostream>
#include <unistd.h>
#include <thread>

class Logger;

template <typename T>
class BaseSingleton {
protected:
    BaseSingleton() = default;
    BaseSingleton(const BaseSingleton&) = delete;
    BaseSingleton& operator =(const BaseSingleton&) = delete;
public:
    static T & Instance() {
        static T m_instance;
        return m_instance;
    }
};

class Logger: public BaseSingleton<Logger> {
private:
    Logger() {
        std::cout << "In C'tor" << std::endl;
    }
    friend class BaseSingleton<Logger>;
    /*
     * friend bec instance of Logger is created by Instance
     * method of BaseSingleton
     */

public:
    void log() {
        std::cout << "In log: " << this << std::endl;
    }
    ~Logger() = default;
};

int main()
{
    std::thread t1{[]() {
            Logger &lg = Logger::Instance();
            lg.log();

            Logger &lg2 = Logger::Instance();
            //lg2 = lg; // Error as operator= is private

            Logger &lg3 = lg;
            lg3.log();
        }
    };
    std::thread t2{[]() {
            Logger &lg = Logger::Instance();
            lg.log();
        }
    };

    t1.join();
    t2.join();

    return 0;
}

/*
 * Output
    In C'tor
    In log: 0x55a20cc94152
    In log: 0x55a20cc94152
    In log: 0x55a20cc94152
 */

