/*
 * run: g++ singleton_0.cpp
 * demonstrates you need to delete copy C'tor as well as
 * assignment operator as well
 */


#include <iostream>
#include <stdio.h>

class Logger
{
private:
    Logger() = default;
    //Logger(const Logger&) = delete ;
    //Logger & operator=(const Logger&) = delete ;
public:
    static Logger & Instance() {
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
    Logger lg = Logger::Instance();
    lg.log(); // prints different address
    Logger lg1 = Logger::Instance();
    lg1.log(); // prints different address
    Logger lg2 = lg1;
    lg2.log(); // prints different address
    return 0;
}

/*
 * Output
    In log: 0x7ffcdf72eba5
    In log: 0x7ffcdf72eba6
    In log: 0x7ffcdf72eba7
 *
 */

