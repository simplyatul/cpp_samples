
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "greatestOfThree.h"

TEST_CASE( "greatestOfThree test", "[greatestOfThree test]" ) {

    auto a = 55;   
    auto b = 5;   
    auto c = 75;   
    REQUIRE(75 == GreatestOfThree(a,b,c));
    
}
