#include <iostream>
#include "greatestOfThree.h"

int main()
{
 // your code goes here
 int a,b,c;
 std::cout<< "Enter 3 digits" << std::endl;
 std::cin>>a>>b>>c;
 std::cout<<"Greatest Of Three is: " << GreatestOfThree(a,b,c)<< std::endl;
 return 0;
}
