#include <vector>
#include <iostream>

// std::move is cast to an rvalue that expresses the intention of moving

void noop_example() {

  std::vector<int> v0{1,2,3,4};

	std::move(v0); // No-Op
	// above implies move expresses the intention of moving	

	// So following is perfectly safe
	std::cout << v0.size() << std::endl; // prints 4

}

std::vector<int> return_example() {
	
	std::vector<int> v0{1,2,3,4,5};

	//Wrong: 
	// return std::move(v0);

	// Above works but it is unnecessary and
	// sometimes prevents RVO (Return Value Optimization)

	// correct
	return v0;
}

int main() {
	
	std::vector<int> v0{1,2,3,4};

	auto v1 = std::move(v0); // v0 won't be used anymore

	std::cout << v0.size() << std::endl; // prints 0

	// how std::move works
	// Ref: https://en.cppreference.com/w/cpp/utility/move
	auto v2 = static_cast<std::vector<int>&&>(v1);
 
	std::cout << v1.size() << std::endl; // prints 0
	std::cout << v2.size() << std::endl; // prints 4

	noop_example();
}


/*
Ref: https://en.cppreference.com/w/cpp/container/vector/vector
see vector( vector&& other ); is added in C++11

*/
