#include <iostream>

/*Enable following line to use Boost threads */
#define USE_BOOST

#ifdef USE_BOOST
    #include <boost/thread.hpp>
    #define THRD boost::thread
    #define USING_THRD_LIB "Using Boost Threads"
#else
    #include <thread>
    #define THRD std::thread
    #define USING_THRD_LIB "Using Std Threads"
#endif

class Task
{
public:
    void execute(std::string command)
    {
        for(int i = 0; i < 5; i++)
        {
            std::cout<<command<<" :: "<<i<<std::endl;
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
    std::cout << USING_THRD_LIB << std::endl;
    Task * taskPtr = new Task();
    // Create a thread using member function
    THRD th(&Task::execute, taskPtr, "Task w/ Member Function");
    th.join();
    delete taskPtr;

    // Create a thread using static function
    THRD th1(&Task::stMemFn, "Task w/ Static Function");
    th1.join();
    return 0;
}
