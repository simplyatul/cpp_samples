#include <iostream>
#include <boost/thread/thread.hpp>
#include <boost/chrono.hpp>

// thread interrupting sample

class Task
{

public:
   bool exit;
    Task(): exit(false) {}

    void execute(std::string command)
    {
        for(int i = 0; i < 5; i++)
        {
            std::cout<<command<<" :: "<<i<<std::endl;
            boost::this_thread::sleep_for(boost::chrono::seconds(1));
            // sleep(1); // th->interrupt() will work with normal sleep
            if(true == exit) {
                std::cout<<command<<"Breaking... "<<std::endl;
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
    boost::thread *th = new boost::thread(&Task::execute, taskPtr, "Task w/ Member Function");
    sleep(2);
    th->interrupt();
    //taskPtr->exit=true;
    th->join();
    delete taskPtr;
    delete th;

    return 0;
}
