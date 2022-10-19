/*
 * run: g++ weak_ptr_0.cpp
 * Here, D'tors Employee and Project class are not called
 * bec shared_ptr created circular relationshiop 
 */

#include <iostream>
#include <memory>

class Employee;
class Project {
public:
    std::shared_ptr<Employee> m_emp;
    Project() {
        std::cout << "Project C'tor\n" ;
    }

    ~Project() {
        std::cout << "Project D'tor\n" ;
    }
};

class Employee {
public:
    std::shared_ptr<Project> m_prj;
    Employee() {
        std::cout << "Employee C'tor\n" ;
    }

    ~Employee() {
        std::cout << "Employee D'tor\n" ;
    }
};

int main() {
    std::shared_ptr<Project> p (new Project);
    std::shared_ptr<Employee> e (new Employee);
    p->m_emp = e;
    e->m_prj = p;

    return 0;
}

