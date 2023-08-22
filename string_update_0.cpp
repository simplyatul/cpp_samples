/*
 * run: g++ string_update_0.cpp
 * Refer problem statement at 
 * https://raw.githubusercontent.com/simplyatul/java_samples/master/src/main/java/com/simplyatul/java_samples/StringUpdate.java
 */

#include <iostream>
#include <unordered_map>
#include <list>
#include <cstdint>
#include <utility>

using namespace std;
const static string T1 = "AB";
const static string T2 = "BA";
const static string T3 = "CD";
const static string T4 = "DC";

static bool replaceIfy(string & S , string replaceWith) {
    auto index = S.find(replaceWith);
    if (index != std::string::npos) {
        S.replace(index, replaceWith.length(), "");
        return true;
    }
    return false;
}

string solution(const string S) {
    string str = S;
    while(str.length() > 0 ) {
        if (replaceIfy(str, T1)) continue;
        if (replaceIfy(str, T2)) continue;
        if (replaceIfy(str, T3)) continue;
        if (replaceIfy(str, T4)) continue;
        break;
    }

    return str;
}

int main() {
    string s = "AACBDB";
    cout << "Sol: " << solution(s) << endl;
    return 0;
}