/*
run: g++ fizzbuzz.cpp

Refer fizzBuzz function for the ask

Input 15
Expected Output
1
2
Fizz
4
Buzz
6
7
8
Fizz
Buzz
11
Fizz
13
14
FizzBuzz
*/

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);


/*
 * Complete the 'fizzBuzz' function below.
 *
 * The function accepts INTEGER n as parameter.
 */
#define A 3
#define B 5
#define AB_PROD (A*B)

void fizzBuzz(int n) {
    for (int k =1; k <=n; k++) {
        if(0 == k % AB_PROD) {			// k is divided by both A and B
            cout << "FizzBuzz\n";	
        } else if (0 == k % A) {		// k is divided by A but not by B
            cout << "Fizz\n";
        }else if (0 == k % B) {			// k is divided by B but not by A
            cout << "Buzz\n";
        } else {
            cout << k << '\n';			// k is neither divided by A and B
        }
    }
}

int main()
{
    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    fizzBuzz(n);

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}


