/*
 * run: g++ auto_0.cpp
 */
#include <iostream>
#include <string>
#include <typeinfo>

#define TYPEOF(__var__) std::cout << "Type of " << #__var__ << " : " << typeid(__var__).name() << '\n';
	
#define PRINT_NAME(x) std::cout << #x << " - " << typeid(x).name() << '\n'

int main() {
  
  int i=0;
  const int ci = i, &cr = ci;
  auto b = ci;  // b is an int (top-level const in ci is dropped) 
  TYPEOF(b);
  auto c = cr;  // c is an int (cr is an alias for ci whose const is top-level)
  TYPEOF(c);
  auto d = &i;  // d is an int*(& of an int object is int*)
  TYPEOF(d);
  auto e = &ci; // e is const int*(& of a const object is low-level const)
  TYPEOF(e);

  // If we want the deduced type to have a top-level const, we must say so explicitly:
  const auto f = ci; // deduced type of ci is int; f has type const int
  TYPEOF(f);

  auto &g = ci;       // g is a const int& that is bound to ci
  TYPEOF(g);
  //auto &h = 42;       // error: we can't bind a plain reference to a literal
  const auto &j = 42; // ok: we can bind a const reference to a literal
  TYPEOF(j);

	auto year { 2020 }; TYPEOF(year); 
	auto& year_ref = year; TYPEOF(year_ref);
	const auto& year_cref = year; TYPEOF(year_cref);
	auto* year_ptr = &year; TYPEOF(year_ptr);
	const auto* year_cptr = &year; TYPEOF(year_cptr);

  std::string s("Hello World!!!");
  auto punct_cnt = s.size();
  TYPEOF(punct_cnt);

  decltype(s.size()) punct_cnt1 = 0;
  TYPEOF(punct_cnt1);

  std::cout << "-------------------------------------" << std::endl;
  TYPEOF(char);
  TYPEOF(const char);
  TYPEOF(unsigned char);
  TYPEOF(char *);
  TYPEOF(const char *);
  TYPEOF(long);
  TYPEOF(long long);
  TYPEOF(int&&);
  TYPEOF(int&);
  TYPEOF(unsigned int);
  TYPEOF(short);
  TYPEOF(size_t);

}
