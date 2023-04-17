/*
 * run: g++ sizeof_0.cpp
 */


#include <iostream>

template <typename T>
struct SizeOfT {
    enum {
        value = sizeof(T) };
    SizeOfT() {
      std::cout << typeid(T).name() << " " << value << "\n";
    }
};

// C++11 and beyond
template <typename T>
struct SizeOfT_C11 {
    static constexpr int value = sizeof(T);
    SizeOfT_C11() {
      std::cout << typeid(T).name() << " " << value << "\n";
    }
};

class Zero {
};

int main()
{
    SizeOfT<int32_t *> a; // Pi 8
    SizeOfT<uint32_t *> b; // Pj 8
    SizeOfT<short *> c; // Ps 8
    SizeOfT<void *> d; // Pv 8
    SizeOfT<char> e; // c 8
    SizeOfT<Zero> f; // 4Zero 1

    SizeOfT_C11<short> g; // s 2
    SizeOfT_C11<double> h; // d 8
}


