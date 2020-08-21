#include <iostream>

using namespace std;

// function returning lvalue reference
int& foo() {
	static int i=5;
	cout << __func__ << ":" << __LINE__ << ": " << i << endl;
	return i;
}

int main() 
{
	cout << __func__ << ":" << __LINE__ << endl;
	int& foo(); // declaration of function
	cout << __func__ << ":" << __LINE__ << endl;
	&foo(); // calls the function
	cout << __func__ << ":" << __LINE__ << endl;
	foo() = 10; // calls the function
	cout << __func__ << ":" << __LINE__ << endl;
	foo();	// calls the function. i will be 10
	cout << __func__ << ":" << __LINE__ << endl;
	return 0;
}

