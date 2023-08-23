/*
 * run: g++ vector_0.cpp
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

bool cmp(const int& a, const int& b) {
	// sorts in ascending order (1, 2, 3,...)
	// should not compare with <= Or >=
	return a < b;
}
int main() {  
	std::vector<int> x{ 0, 1, 8, 13, 5, 2, 3 }; 
	x[0] = 21;
	x.push_back(1);

	std::cout << "Orig Vector: \n";
	for (auto number : x) {
		std::cout << number << std::endl;
	}

	std::sort(x.begin(), x.end(), cmp);
	std::cout << "Printing " << x.size() << " Fibonacci numbers.\n";
	for (auto number : x) {
		std::cout << number << std::endl;
	}
}

