/*
 * run: g++ map_0_user_defined_key.cpp --std=c++17
 * Demonstrate how to use User defined class as a Key of a map 
 */
 
#include <iostream>
#include <map>
#include <string>

using namespace std;

class Student {
private:
    string name;
    int id;
public:
    Student(string n, int i): name(n), id(i) {}
    string getName() const {
        return name;
    }
    int getId() const {
        return id;
    }
    
    bool operator <(const Student& s) const {
        if(s.name > this->name) return true;
        return false;
    }
};

struct StudentIdComparator {
    bool operator() (const Student &left, const Student &right) const {
        if(left.getId() < right.getId()) return true;
        return false;
    }
};



#define INSERT_DATA(mymap) mymap.insert(std::pair<Student, int>(Student("Ram", 20), 20)); \
    mymap.insert(std::pair<Student, int>(Student("Sham", 50), 50)); \
    mymap.insert(std::pair<Student, int>(Student("Kiran", 500), 5));

void insertIntoMap(std::map<Student, int> &s) {
    INSERT_DATA(s)
}

void insertIntoMap(std::map<Student, int, StudentIdComparator> &s) {
    INSERT_DATA(s)
}


int main()
{
    std::map<Student, int> s1Map;
    insertIntoMap(s1Map);
    cout << "Sorted by Name using operator <" << endl;
    for (const auto &it: s1Map) {
        cout << it.first.getName() << " " << it.first.getId() << endl;
    }
    
    std::map<Student, int, StudentIdComparator> s2Map;
    insertIntoMap(s2Map);
    cout << endl << "Sorted by Id using comparator operator ()" << endl;
    for (const auto &it: s2Map) {
        cout << it.first.getName() << " " << it.first.getId() << endl;
    }
}

