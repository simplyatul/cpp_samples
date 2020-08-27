
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "greatestOfThree.h"

TEST_CASE( "greatestOfThree test", "[greatestOfThree test]" ) {
    int a,b,c;
    a = 55; b = 5; c = 75;   
    REQUIRE(75 == GreatestOfThree(a,b,c));
    a = 5; b = 55; c = 75;   
    REQUIRE(75 == GreatestOfThree(a,b,c));
    a = 5; b = 75; c = 55;   
    REQUIRE(75 == GreatestOfThree(a,b,c));
}
