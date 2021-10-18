/*
 * run: g++ enum_0.cpp 
 * Various ways to convert enum to string
 */
#include "common.h"

#define ENUM_TO_STR(constant) \
	case constant:	return #constant;


typedef enum {
    ZERO=0,
    ONE,
    TWO,
    THREE
}NUMBER;

const char *
getNumberString(NUMBER n)
{
    switch(n)
    {
        case ZERO: return "ZERO";
        default: return "Unknown";
    }
}

typedef enum {
    RED=4, // error if 0
    BLACK
}Color;

enum class Birds {
    Robin,
    Kingfisher,
    Swift,
    HummingBird
};

const char *
getBirdsString(Birds b) {
    switch (b)
    {   
        case Birds::Robin: return "Robin";
        default:
            return "Unknown";
    }
}

const char *
getStringNumber(int value, const char *unknownValueString) {
    switch (value)
    {
        ENUM_TO_STR(ZERO);
        ENUM_TO_STR(RED);
        default:
            return unknownValueString;
    }
}

int main()
{
    cout << getStringNumber(ZERO, ""); printf("\n");
    cout << getStringNumber(RED, ""); printf("\n");
    cout << getBirdsString(Birds::Robin); printf("\n");
    cout << getNumberString(ZERO); printf("\n");
    return 0;
}
