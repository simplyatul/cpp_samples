/*
 * run: g++ thread_4.cpp -lboost_thread -lpthread -lboost_chrono
 */


#include <iostream>
#include <boost/thread/thread.hpp>
#include <boost/chrono.hpp>

// thread interrupting sample

class Task
{
private:
    const std::string cn;
public:
   bool exit;
    Task(): cn(__func__), exit(false) {
        
    }

    void execute(std::string command)
    {
        const std::string logPrefix = cn + "::" + std::string(__func__) + ": ";
        for(int i = 0; i < 5; i++)
        {
            std::cout<<command<<" :: "<<i<<std::endl;
            boost::this_thread::sleep_for(boost::chrono::seconds(1));
            // sleep(1); // boost::thread::interrupt() will work with normal sleep
            if(false == exit) {
                std::cout<< logPrefix << command<<"Breaking... "<<std::endl;
                break;
            }
        }
    }

    static void stMemFn(std::string command)
    {
        for(int i = 0; i < 5; i++)
        {
            std::cout<<command<<" :: "<<i<<std::endl;
        }
    }
};

int main()
{
    Task * taskPtr = new Task();
    // Create a thread using member function
    boost::thread *th = nullptr;
    th = new boost::thread(&Task::execute, taskPtr, "Task w/ Member Function");
    //th->detach();
    sleep(5);
    //th->interrupt();
    taskPtr->exit=true;
    std::cout << "joinable: " << th->joinable() << std::endl;
    std::cout << "before join" << std::endl;
    th->join();
    std::cout << "post join" << std::endl;
    delete taskPtr;
    delete th;

    return 0;
}
