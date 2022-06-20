/*
 * run: g++ singleton_7.cpp --std=c++17
 * Solution to problem stated in singleton_6.cpp
 *
 * This uses Registry of Singletons => Multiton methology
 * Types of printers are maintained in PrinterProvider
 * When PrinterProvider::registerCreator, it
 */

#include <iostream>
#include <unistd.h>
#include <unordered_map>
#include <functional>
#include <memory>
#include <mutex>
class Printer;

using PrinterPtr = std::shared_ptr<Printer>;
using Creator = std::function<PrinterPtr()>;
/*
 * std::function is used instead of callback.
 * As it can store any type of callable
 */

class Printer {
protected:
    Printer() = default;
public:
    Printer(const Printer&) = delete ;
    Printer & operator=(const Printer&) = delete ;
    virtual ~Printer() = default;

    virtual void Print(const std::string & data) = 0;

    static PrinterPtr Instance();
};


class PrinterProvider {
private:
    PrinterProvider() = default;
    struct InstanceInfo {
        PrinterPtr m_Printer{};
        Creator m_Creator{};
    };
    inline static std::mutex m_mtx;
    inline static std::unordered_map<std::string, InstanceInfo> m_Printers{};
public:
    static void registerCreator(const std::string &key, Creator creator) {
        std::lock_guard<std::mutex>  lock{m_mtx};
        if(auto it=m_Printers.find(key); it == end(m_Printers)) {
            m_Printers[key].m_Creator = creator;
            std::cout << "Registering Printer" << std::endl;
        } else {
            std::cout << "Already Registered\n";
        }
    }
    static PrinterPtr getPrinter(const std::string &key) {
        std::lock_guard<std::mutex> lock { m_mtx };
        if (auto it = m_Printers.find(key); it != end(m_Printers)) {
            if(!m_Printers[key].m_Printer) {
                std::cout << "Creating Printer Instance" << std::endl;
                m_Printers[key].m_Printer = m_Printers[key].m_Creator();
            }
            return m_Printers[key].m_Printer;
        }
        std::cout << "Unknown Key\n";
        return nullptr;
    }
};

class LocalPrinter: public Printer
{
private:
    LocalPrinter() {
        std::cout << "Instance of LocalPrinter created" << std::endl;
    }

public:
    static PrinterPtr Instance() {
        return std::shared_ptr<Printer> {new LocalPrinter{}};
    }

    void Print(const std::string & data) {
        std::cout << "Printing " << data << std::endl;
    }

    ~LocalPrinter() = default;
};

void PrintCostSheet() {
    auto p = PrinterProvider::getPrinter("Local");
    if(p) {
        p->Print("Cost Sheet");
    }
}

int main() {
    PrinterProvider::registerCreator("Local", &LocalPrinter::Instance);
    /*
     * Now if a new printer is added, then no code changes
     * are required in Printer (Base/Interface) class.
     */
    PrintCostSheet();
    return 0;
}
