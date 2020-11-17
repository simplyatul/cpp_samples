#include <iostream>
#include <boost/thread.hpp>

using namespace std;

class my_thread {
  private:
    int id;
  public:
    my_thread(int k): id(k){}
 
    void operator() () {
        // Thread starts here
        cout << __func__ << ":" << __LINE__ << " id: " << id << endl;
        //cout << "Thread Id: " << boost::thread::id() << endl; // this prints {Not-any-thread}
        cout << "Thread Id: " << boost::this_thread::get_id() << endl;
    }

};


int main() {
    cout << "Main Thread Id: " << boost::this_thread::get_id() << endl;
    my_thread t1(1);
    t1(); // Calls operator() (). But does not actually spawn a new thread.

    my_thread mt(2);
    boost::thread mt1{mt}; // Spawns a new thread running mt
    cout << "mt1 id: " << mt1.get_id() << endl;
    sleep(1);
    return 0;
}
