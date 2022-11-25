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
    Logger() {
        std::cout << "In c'tor" << std::endl;
    }
    //Logger(const Logger&) = delete ;
    //Logger & operator=(const Logger&) = delete ;
public:
    Logger(Logger&) {
        std::cout << "In copy c'tor" << std::endl;
    }

    Logger(const Logger&) {
        std::cout << "In const copy c'tor" << std::endl;
    }

    Logger & operator=(const Logger& l) {
         std::cout << "In assignment operator" << std::endl;
         return *this;
    }

    static Logger & Instance() {
        static Logger m_instance;
        std::cout << "Static object: " << &m_instance << std::endl;
        return m_instance;
    }

    void log() const {
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
    const Logger lg1 = Logger::Instance();
    lg1.log(); // prints different address
    std::cout << std::endl;

    std::cout << "lg2 object " << std::endl;
    Logger lg2 = lg1;
    lg2.log(); // prints different address
    std::cout << std::endl;

    std::cout << "assignment" << std::endl;
    lg2 = lg1;
    std::cout << std::endl;

    std::cout << "Pointer" << std::endl;
    Logger *ptr = &Logger::Instance();
    Logger lg3 = *ptr;
    return 0;
}


/*
 * Output
  
lg object 
In c'tor
Static object: 0x4041d2
In copy c'tor
In log: 0x7fff84b73277

lg1 object 
Static object: 0x4041d2
In copy c'tor
In log: 0x7fff84b73276

lg2 object 
In const copy c'tor
In log: 0x7fff84b73275

assignment
In assignment operator

Pointer
Static object: 0x4041d2
In copy c'tor

*
*/

