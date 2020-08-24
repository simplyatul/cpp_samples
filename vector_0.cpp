#include <iostream>

#include <vector>
#include <algorithm>
#include <iostream>

int main() {  
	std::vector<int> x{ 0, 1, 8, 13, 5, 2, 3 }; 
	x[0] = 21;
	x.push_back(1);

	std::cout << "Orig Vector: \n";
	for (auto number : x) {
		std::cout << number << std::endl;
	}

	std::sort(x.begin(), x.end());
	std::cout << "Printing " << x.size() << " Fibonacci numbers.\n";
	for (auto number : x) {
		std::cout << number << std::endl;
	}
}

