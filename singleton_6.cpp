/*
 * run: g++ singleton_6.cpp
 * Solution to problem stated in singleton_5.cpp
 */

#include <iostream>
#include <unistd.h>

class Printer {
protected:
    Printer() = default;
public:
    Printer(const Printer&) = delete ;
    Printer & operator=(const Printer&) = delete ;
    virtual ~Printer() = default;

    virtual void Print(const std::string & data) = 0;

    static Printer & Instance(const std::string & type);
};


class LocalPrinter: public Printer
{
private:
    LocalPrinter() = default; 

public:
    static LocalPrinter & Instance() {
        static LocalPrinter m_instance;
        return m_instance;
    }

    void Print(const std::string & data) {
        std::cout << "Printing " << data << std::endl;
    }

    ~LocalPrinter() = default;
};

Printer & Printer::Instance(const std::string & type) {
    if("Local" == type) {
        return LocalPrinter::Instance();
    }
} 

void PrintCostSheet() {
    Printer::Instance("Local").Print("Cost sheet");
}

int main() {
    auto &p = Printer::Instance("Local");
    p.Print("printing to local printer");
    PrintCostSheet();
    return 0;
}
