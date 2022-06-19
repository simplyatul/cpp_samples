/*
 * run: g++ singleton_5.cpp
 * By using the Singleton class name directly violets 
 * dependency inversion principle (i.e program to interface, 
 * not to implementation).   
 *
 * It is difficult to replace with other class. 
 * This makes unit testing difficult too. You can not 
 * mock the usage with the mock object.
 */

#include <iostream>
#include <unistd.h>

class LocalPrinter
{
private:
    LocalPrinter() = default; 

public:
    LocalPrinter(const LocalPrinter&) = delete ;
    LocalPrinter & operator=(const LocalPrinter&) = delete ;

    static LocalPrinter & Instance() {
        static LocalPrinter m_instance;
        return m_instance;
    }

    void Print(const std::string & data) {
        std::cout << "Printing " << data << std::endl;
    }

    ~LocalPrinter() = default;
};

void PrintCostSheet() {
    LocalPrinter::Instance().Print("Cost sheet");
    /*
     * Here, LocalPrinter name is used directly. 
     *
     * In future, LocalPrinter can not be replaced with Network 
     * Printer if we want to do so
     */
}

int main() {
 
    auto &p = LocalPrinter::Instance();
    p.Print("printing to local printer");
    PrintCostSheet();
    return 0;
}
