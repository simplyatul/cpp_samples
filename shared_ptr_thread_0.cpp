/*
 * run: g++ shared_ptr_thread_0.cpp -lpthread
 * 
 * standard guarantees -
 * 1. shared pointer reference counting is handled in thread safe way 
 * 2. only one thread (holding last reference) will call delete on shared object
 * 3. shared_ptr does not guarantee any thread safety for object stored in it
 *
 * Ref:
 * https://stackoverflow.com/questions/9127816/stdshared-ptr-thread-safety-explained
 * https://en.cppreference.com/w/cpp/memory/shared_ptr
 */

#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <mutex>
 
struct Base
{
    Base() { std::cout << "  Base::Base()\n"; }
    // Note: non-virtual destructor is OK here
    ~Base() { std::cout << "  Base::~Base()\n"; }
};
 
struct Derived: public Base
{
    Derived() { std::cout << "  Derived::Derived()\n"; }
    ~Derived() { std::cout << "  Derived::~Derived()\n"; }
};
 
void fun(std::shared_ptr<Base> p) {
    std::cout << "fun: local pointer in a thread:\n"
                  << "  lp.get() = " << p.get()
                  << ", lp.use_count() = " << p.use_count() << '\n';
}

void thr(std::shared_ptr<Base> p)
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::shared_ptr<Base> lp = p; // thread-safe, even though the
                                  // shared use_count is incremented
    {
        static std::mutex io_mutex;
        std::lock_guard<std::mutex> lk(io_mutex);
        // above mutex may not require as get and use_count 
        // functions are const functions.
        std::cout << "local pointer in a thread:\n"
                  << "  lp.get() = " << lp.get()
                  << ", lp.use_count() = " << lp.use_count() << '\n';
    }
}
 
int main()
{
    std::shared_ptr<Base> p = std::make_shared<Derived>();
 
    std::cout << "Created a shared Derived (as a pointer to Base)\n"
              << "  p.get() = " << p.get()
              << ", p.use_count() = " << p.use_count() << '\n';
    
    fun(p);

    std::cout << "Post fun\n"
              << "  p.get() = " << p.get()
              << ", p.use_count() = " << p.use_count() << '\n';

    std::thread t1(thr, p), t2(thr, p), t3(thr, p);
    p.reset(); // release ownership from main
    std::cout << "Shared ownership between 3 threads and released\n"
              << "ownership from main:\n"
              << "  p.get() = " << p.get()
              << ", p.use_count() = " << p.use_count() << '\n';
    t1.join(); t2.join(); t3.join();
    std::cout << "All threads completed, the last one deleted Derived\n";
}
