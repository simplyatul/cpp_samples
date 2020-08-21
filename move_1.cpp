#include <vector>
#include <utility>
#include <tuple>

/*
Many classes in std library is move aware
    - std::pair
    - std::tuple

Some classes represents "unique ownership" and are move-only

*/

struct foo
{
};

void pair_and_tuple()
{

	std::pair<foo, int> p;
	auto p_copy = p;
	auto p_move = std::move(p);
	// if foo has move c'tor and move assignment opeator
	// then above std::move will call it as appropriate 
	/* Ref: https://en.cppreference.com/w/cpp/utility/pair/pair
 	
			template< class U1, class U2 >
			pair( pair<U1, U2>&& p );
	*/

	std::tuple<foo, int, char> t;
	auto t_copy = t;
	auto t_move = std::move(t);
	
	// Ref: https://en.cppreference.com/w/cpp/utility/tuple/tuple 
}

/*
Every container in c++ is move aware in one way or the another

*/

void containers()
{
	// Every container in c++ is move aware in in==one way to another

	std::vector<foo> v;
	auto v_copy = v;
	auto v_move = std::move(v);
	
	// Moves temporary inside the vector
	v.push_back(foo{}); // no copies peformed

	foo f;
	// Copies 'f' inside vector
	v.push_back(f);


	// Moves 'f' inside vector
	v.push_back(std::move(f));

	// Ref: https://en.cppreference.com/w/cpp/container/vector/push_back
	// void push_back( T&& value );

}


int main()
{

	return 0;
}
