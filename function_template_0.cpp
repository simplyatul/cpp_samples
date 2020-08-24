#include <iostream>

template <typename T>
T add(T x, T y, T z) { 
  return x + y + z;
}

using namespace std;

int main() {
	
	auto a = add(1, 2, 3); cout << a << endl;
	auto b = add(1L, 2L, 3L); cout << b << endl;
	auto c = add(1.F, 2.F, 3.F); cout << c << endl;

}
