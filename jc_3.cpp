#include <vector>
#include <map>
#include <iostream>
#include <unordered_set>
#include <sstream>
#include <iomanip>

using namespace std;

bool isIntersecting(const string& S) {
     unordered_set<char> digitSet;
     for(auto a: S) {
        if(a != ':') {
            digitSet.insert(a);
        }
        if(digitSet.size() > 2) {
            return false;
        }
     }
    return true;
}

bool incSec(string& s, int sI, int Max) {
    int d = atoi(s.substr(sI,2).c_str());
    d++;
    bool carry = false;
    if(d>=Max) {
        carry = true;
        d=0;
    } 
    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << d;
    s.replace(sI, 2, ss.str());

    return carry;
}

bool incHr(string& s, int sI) {
    return incSec(s, sI, 24);
}

bool incMin(string& s, int sI) {
    return incSec(s, sI, 60);
}

string incByOneSec(const string& S) {

    string n = S;
    if(true == incSec(n,6,60)) {
        if(true == incMin(n,3)) {
            incHr(n,0);
        }

    }
    return n;
}

int solution(string &S, string &T) {
    // Implement your solution here
    string curr = S;
    int intersectingPoints=0;
    do {

        if(isIntersecting(curr)) {
            intersectingPoints++;
        }
        if(0 == curr.compare(T)) {
            break;
        }
        curr = incByOneSec(curr);
        //cout << "curr: " << curr << endl;

    } while(true);

    return intersectingPoints;
}



int main() {
    string s = "01:05:00";
    string s1 = s.substr(3,2);

    //map<string, string> inputs;
    vector < pair<string, string> > input = {
        { make_pair("00:00:00", "00:00:00") },
        { make_pair("00:59:59", "01:00:00") },

        { make_pair("00:00:00", "00:00:10") },
        { make_pair("15:15:00", "15:15:12") },
        { make_pair("22:22:21", "22:22:23") },

        { make_pair("00:00:00", "00:00:00") },
        { make_pair("13:31:33", "13:31:33") },
        { make_pair("02:20:22", "02:20:22") },
        { make_pair("15:45:14", "15:45:14") }
    };

    for(auto i: input) {
        cout << "Pair " << i.first << " - " << i.second << " Sol: " << solution(i.first, i.second) << endl;
    }

    cout << "Hi\nReady for the test\n";
    return 0;
}

