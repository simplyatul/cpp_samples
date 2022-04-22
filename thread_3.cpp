#include <iostream>
#include <boost/thread/thread.hpp>
#include <boost/chrono.hpp>

/* 
 Interrupting the thread
 run: g++ thread_3.cpp -lboost_thread -lpthread -lboost_chrono

*/

#define LOGTIME \
    std::cout << std::time(nullptr) << ": " << __FUNCTION__ << ":" << __LINE__ << std::endl


class A
{
public:
    A() {
        LOGTIME;
    }
    ~A() {
        LOGTIME;
    }
};

class Task
{

public:
   bool exit;
    Task(): exit(false) {}

    void execute(std::string command)
    {
            LOGTIME;
        sleep(5);
            LOGTIME;
        for(int i = 0; i < 5; i++)
        {
            std::cout<<command<<" :: "<<i<<std::endl;
            LOGTIME;
            try {
                boost::this_thread::sleep_for(boost::chrono::seconds(10)); 
            } catch(boost::thread_interrupted const& )
            {
                //clean resources
                std::cout << "Worker thread interrupted" << std::endl;
                return;
            }
            LOGTIME;
            A a;
            /* 
             * If interrupt is called then 
             * thread will straight away existing when above 
             * sleep is called. So following line of code would not execute
             * there after 
             */
            LOGTIME;
            sleep(10); // boost::thread::interrupt() will not work with normal sleep
            LOGTIME;
            if(true == exit) {
                std::cout<<command<<" Breaking... "<<std::endl;
                break;
            }
            LOGTIME;
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
    sleep(2);
    LOGTIME;
    th->interrupt(); // *** Use with care.
    LOGTIME;
    //taskPtr->exit=true;
    th->join();
    delete taskPtr;
    delete th;

    return 0;
}
