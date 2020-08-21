#include <iostream>

void foo(int& p) {
	p = 11;
	std::cout << "non-const lvalue ref\n";
}

void foo(int&& p) {
	p = 10;
	std::cout << "non-const rvalue ref\n";
}


void bar(const int& p) {
	// p = 10;	// error
	std::cout << "const lvalue ref: " << p << std::endl ;
}

int main() {

  // compiler correctly selects the above overloads

	int a = 0;
	foo(a);
	foo(5);

	bar(a);
 	bar(5);
}
