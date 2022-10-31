/*
 * run: g++ deleter_0.cpp
 * 
 */

#include <iostream>
#include <memory>

// Here is your legacy code
void legacyCode() {
    int *p = (int *) malloc(4);
    *p = 100;
    std::cout << *p << std::endl;
    free(p);
}

/*
 * and if you used smart pointer just to wrap around
 * your legacy code then it won't work. 
 * Following will produce undefined behavior.
 * Bec unique_ptr will call standard deleter which calls
 * delete on the pointer  
 */

void legacyCodeUsingSmartPointer() {
    std::unique_ptr<int> p {(int *) malloc(4)};
    *p = 100;
    std::cout << *p << std::endl;
    //free(p);
}

/*
 * Solution is to used customer deleter (Either with Function Object or with Function )
 * In following, Free is function object. 
 * You can declare Free as class too. 
 * struct makes everything public and is convenient for this use case
 *
 * function object is a function which has a state
 * you can create function object by overloading function called operator
 */

 struct Free {
     void operator()(int *p) {
         std::cout << "Free: pointer freed\n";
         free(p);
     }
 };

void legacyCodeWithFunctionObjectAsDeleter() {
    std::unique_ptr<int, Free> p {(int *) malloc(4), Free{}};
    *p = 100;
    std::cout << *p << std::endl;
}

/*
 * One can use function as custom deleter as well
 */

void FreeMalloc(int *p) {
    std::cout << "FreeMalloc: pointer freed\n";
    free(p);
}

void legacyCodeWithFunctionAsDeleter() {
    std::unique_ptr<int, void(*)(int *p)> p {(int *) malloc(4), FreeMalloc};
    *p = 100;
    std::cout << *p << std::endl;
}

/*
 * In case of shared pointer, no need to specify 
 * type of the deleter (function or function object both) 
 * as template argument
 */

void legacyCodeWithFunctionAsDeleterAndWithSharedPtr() {
    {
        std::shared_ptr<int> p {(int *) malloc(4), FreeMalloc};
        *p = 100;
        std::cout << *p << std::endl;
    }
    
    {
        std::shared_ptr<int> p {(int *) malloc(4), Free{}};
        *p = 100;
        std::cout << *p << std::endl;
    }
}

int main() {
    legacyCode();
    legacyCodeUsingSmartPointer();
    legacyCodeWithFunctionObjectAsDeleter();
    legacyCodeWithFunctionAsDeleter();
    legacyCodeWithFunctionAsDeleterAndWithSharedPtr();
    return 0;
}
