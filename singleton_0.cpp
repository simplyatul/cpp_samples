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
    Logger(const Logger&) {
        std::cout << "In copy c'tor" << std::endl;
    }

    Logger & operator=(const Logger& l) {
         std::cout << "In assignment operator" << std::endl;
         return *this;
    }

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
    std::cout << "lg object " << std::endl;
    Logger lg = Logger::Instance();
    lg.log(); // prints different address
    std::cout << std::endl;

    std::cout << "lg1 object " << std::endl;
    Logger lg1 = Logger::Instance();
    lg1.log(); // prints different address
    std::cout << std::endl;

    std::cout << "lg2 object " << std::endl;
    Logger lg2 = lg1;
    lg2.log(); // prints different address
    std::cout << std::endl;

    std::cout << "assignment" << std::endl;
    lg2 = lg1;
    return 0;
}


/*
 * Output
 
 
lg object 
In copy c'tor
In log: 0x7ffcd273c5ef

lg1 object 
In copy c'tor
In log: 0x7ffcd273c5ee

lg2 object 
In copy c'tor
In log: 0x7ffcd273c5ed

assignment
In assignment operator

*
*/

