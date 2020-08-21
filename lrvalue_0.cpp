
int bar() { return 5;}

int main() {

	// bar() = 0; // error
  // &5;				// error
	// &bar();		// error

	// int& lv_ref0 = 5;			// error
	const int& clv_ref0 = 5;	// but this works

	// int& lv_ref1 = bar();	// error
	
	// Rvalues bind to rvalue references, 
	// introduced in C++11

	int&& rv_ref3 = 5; 
	int&& rv_ref4 = bar(); 

	// e.g. of rvalues 
	// numeric literals
	5;
	10.33f;

	// arithmatic expressions;
	5 + 4 + 5;

	// function call returning non referecens
	bar();

}
