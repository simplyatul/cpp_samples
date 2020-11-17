#include <iostream>
using namespace std;

class my_thread {
  public:
    void operator() () {
        // Thread starts here
        cout << __func__ << ":" << __LINE__ << endl;
    }

    // ... Other members/methods as necessary
};


int main() {
    my_thread t1;
    t1(); // Calls operator() (). But does not actually spawn a new thread.
    return 0;
}
