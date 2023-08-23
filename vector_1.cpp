/*
 * run: g++ vector_1.cpp
 * sorting a vector of custom object
 * Ref: https://stackoverflow.com/questions/1380463/sorting-a-vector-of-custom-objects
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

struct CustomObject {
	int k;
	string s;
	CustomObject(const int &i, const string &a) : k(i), s(a) {}

	// ascending order
	bool operator < (const CustomObject& b) const {
        return (this->k < b.k);
    }
	// descending order
	bool operator > (const CustomObject& b) const {
        return (this->k > b.k);
    }
};

struct less_than_cmp {
	inline bool operator() (const CustomObject& a, const CustomObject& b) {
		return a.k < b.k;
	}
};

int main() {  
	std::vector<CustomObject> x;
	x.push_back(CustomObject(10, "ten"));
	x.push_back(CustomObject(1, "one"));
	x.push_back(CustomObject(-1, "minus one"));
	x.push_back(CustomObject(5, "five"));
	//std::sort(x.begin(), x.end(), less_than_cmp()); // This will work too
	// std::sort(x.begin(), x.end()); // ascending order
	std::sort(x.begin(), x.end(), greater<CustomObject>()); // descending order
	std::cout << "Printing " << x.size() << " elements of CustomObject.\n";
	for (auto o : x) {
		std::cout << o.k << ":" << o.s << std::endl;
	}
}

