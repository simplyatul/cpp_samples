/*
 * run: g++ singleton_1.cpp
 * Correct version of singleton_0.cpp
 */


#include <iostream>
#include <unistd.h>

class Logger
{
private:
    Logger() {
        std::cout << "In C'tor" << std::endl;
    };
public:
       
    Logger(const Logger&) = delete ;
    Logger & operator=(const Logger&) = delete ;

    Logger(const Logger&&) = delete ;   // move constrcutor
    Logger & operator=(const Logger&&) = delete ; // move assignment operator

    /*
     * Note: Scott Meyers mentions in his Effective Modern
     * C++ book, that deleted functions should generally
     * be public as it results in better error messages
     * due to the compilers behavior to check accessibility
     * before deleted status
    */

    // Logger instance is created only when Instance API is called
    static Logger & Instance() {
        /*
         * Mayer's Singleton way
         * from C++11, static construction is thread safe
         */
        static Logger m_instance;
        return m_instance;
    }

    void log() {
        std::cout << "In log: " << this << std::endl;
    }

    ~Logger() = default;
};

int main()
{
    std::cout << "In main " << std::endl;
    sleep(2);
    Logger &lg0 = Logger::Instance(); // This is only allowed
    lg0.log();
    Logger &lg00 = Logger::Instance();
    lg00.log();
    //Logger lg = Logger::Instance(); // Not allowed
    //Logger lg2 = lg0; // Not allowed
    return 0;
}

/*
 * Output
    In main
    In C'tor
    In log: 0x55d35fd43152
    In log: 0x55d35fd43152
 */

