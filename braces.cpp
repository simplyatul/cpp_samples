
/*
run: g++ braces.cpp

Input
2
({})
[[]))

Expected Output
YES
NO

Constraints
1 <= No of Inut strings <= 15
1 <= Lenght of each string <= 100

*/

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);


/*
 * Complete the 'matchingBraces' function below.
 *
 * The function is expected to return a STRING_ARRAY.
 * The function accepts STRING_ARRAY braces as parameter.
 */

#define ROUND_BRACES_OPEN   '('
#define ROUND_BRACES_CLOSE  ')'

#define CURLY_BRACES_OPEN   '{'
#define CURLY_BRACES_CLOSE  '}'

#define SQR_BRACES_OPEN     '['
#define SQR_BRACES_CLOSE    ']'

//#define DEBUG

bool checkIfBalance(const string input) {
    stack<char> s;
#ifdef DEBUG
    cout << input << endl;
    cout << input.size() << endl;
#endif
    for (auto const c: input) {
#ifdef DEBUG
        cout << c << endl;
#endif
        if(s.empty()) {
            s.push(c);
        } else if(ROUND_BRACES_CLOSE == c && ROUND_BRACES_OPEN == s.top()) {
            s.pop();
        } else if(CURLY_BRACES_CLOSE == c && CURLY_BRACES_OPEN == s.top()) {
            s.pop();
        } else if(SQR_BRACES_CLOSE == c && SQR_BRACES_OPEN == s.top()) {
            s.pop();
        } else {
            s.push(c);
        } 
    }
#ifdef DEBUG1
    cout << "Is stack empty : " << s.empty() << endl;
#endif
    return s.empty()? true: false;
}

vector<string> matchingBraces(vector<string> braces) {
    vector<string> result(braces.size());
    for (int i=0; i< braces.size(); i++) {
        // cout << braces[i] << endl;
        if (true == checkIfBalance(braces[i])){
           result[i] = "YES";
        } else {
            result[i] = "NO"; 
        } 
    }
    
    for (auto const s: result) {
        cout << s << endl;
    }
    return result;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string braces_count_temp;
    getline(cin, braces_count_temp);

    int braces_count = stoi(ltrim(rtrim(braces_count_temp)));

    vector<string> braces(braces_count);

    for (int i = 0; i < braces_count; i++) {
        string braces_item;
        getline(cin, braces_item);

        braces[i] = braces_item;
    }

    vector<string> result = matchingBraces(braces);

    for (size_t i = 0; i < result.size(); i++) {
        fout << result[i];

        if (i != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

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

