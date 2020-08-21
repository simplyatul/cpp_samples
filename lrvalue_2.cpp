int main() {

	// lvalue appears on LHS
	int a = 0;
	
	// address of lvalue can be stored in pointer
	int* a_ptr = &a;

	// lvalue can bind to lvalue references
	int& a_ref = a; 

	// e.g. of lvalues
	a;
	
}
