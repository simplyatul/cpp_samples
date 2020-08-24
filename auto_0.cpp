#include <iostream>

#define TYPEOF(__var__) std::cout << typeid(__var__).name() << '\n';
	
int main() {

	auto year { 2020 }; TYPEOF(year); 
	auto& year_ref = year; TYPEOF(year_ref);
	const auto& year_cref = year; TYPEOF(year_cref);
	auto* year_ptr = &year; TYPEOF(year_ptr);
	const auto* year_cptr = &year; TYPEOF(year_cptr);

}
