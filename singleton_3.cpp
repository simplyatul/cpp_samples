/*
 * run: g++ singleton_3.cpp -lpthread
 * Creating single instance of an object using
 * std::call_once. Thread safe solution. However, prefer
 * using Mayer's Single as mentioned in
 * https://en.cppreference.com/w/cpp/thread/call_once as
 *
 * Initialization of function-local statics is guaranteed to occur
 * only once even when called from multiple threads, and may be
 * more efficient than the equivalent code using std::call_once.
 */


#include <iostream>
#include <unistd.h>
#include <thread>
#include <mutex>

std::once_flag flag;

class Logger
{
private:
    Logger() {
        std::cout << "In C'tor" << std::endl;
    };
    Logger(const Logger&) = delete ;
    Logger & operator=(const Logger&) = delete ;
    static Logger *m_pInstance;
public:
    static Logger & Instance() {
        std::call_once(flag, [](){
            m_pInstance = new Logger();
        });
        return *m_pInstance;
    }

    void log() {
        std::cout << "In log: " << this << std::endl;
    }

    ~Logger() = default;
};

Logger *Logger::m_pInstance;

int main()
{
    std::thread t1{[]() {
            Logger &lg = Logger::Instance();
            lg.log();

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
 * Output: Once one instance is created
    In C'tor
    In log: 0x7f0e78000b60
    In log: 0x7f0e78000b60
    In log: 0x7f0e78000b60
 */

