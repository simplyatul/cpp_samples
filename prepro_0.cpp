/*
 * run: g++ prepro_0.cpp 
 */

using namespace std;

#include <iostream>
#include <ctime>

#define ENABLE_TRACE_LOGS

//#define LOG_TRACE(f, t) trace(f,t)
//define LOG_TRACE(...) trace(__VA_ARGS__)
#define LOG_TRACE(fn, ...) trace(string(fn)+":"+to_string(__LINE__)+" ", __VA_ARGS__) // Working
//#define LOG_TRACE(...) trace( __VA_ARGS__) // Working

/*
#ifdef ENABLE_TRACE_LOGS
    #define LOG_TRACE(f, t) trace(f, #t)
#else
    #define LOG_TRACE(f, t)
#endif
*/

void trace(const string func, const string text) {
    cout << "Trace: " << func << ":" << text << endl;
}

std::string getStr() {
    return "Str...";
}

int main()
{
    const std::string function_name = "main"  ;
    cout << "Hi.." << endl;
    trace("main", "log 1");

    LOG_TRACE("main", "log 2");
    int k =3;
    LOG_TRACE("main", "log 2 " + to_string(k));
    LOG_TRACE("main", "log 3 " + getStr());
    LOG_TRACE("main", "log 3 " + getStr() + " log 4");

    LOG_TRACE(function_name, 
        "log 2" 
        " log 3" 
        " log 4");

    return 0;
}
