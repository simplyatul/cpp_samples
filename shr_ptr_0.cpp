
/*
 * run: g++ shr_ptr_0.cpp
 */

#include <string>
#include <iostream>
#include <memory>
#include <cstring>
#include <unistd.h>
#include <queue>
#include <atomic>

typedef struct structTest
{
    int intTest = -1;
    char charTest[32] = {'\0'};
    
}structTest;

std::atomic_uint cnt;

class A
{
private: 
    int c;
public:
    A():m_Test(-1) { c=cnt++; std::cout << "A's C'tor. Cnt: " << c << std::endl; } ;
    int m_Test; 
    virtual ~A(){ std::cout << "A's D'tor. Cnt: " << c << std::endl;}
    
    virtual void toString() { std::cout << m_Test << std::endl; };
};

class B : public A
{

public:
    B(): m_Test(-2) {std::cout << "B's C'tor" << std::endl; };
    int m_Test;
    
    virtual ~B(){ std::cout << "B's D'tor." << std::endl;}
    
    virtual void toString() { std::cout << this->m_Test << std::endl; };
};

B* getObject() {
    return new B();
}

void passRaw(A* a){
    a->toString();
}

void checkNull(std::shared_ptr<A> aPtr) {
    if(aPtr) {
        aPtr->toString();
        std::cout<<"Ref Cnt: " << aPtr.use_count() << std::endl;
    } else {
        std::cout << "aPtr is null" << std::endl;
    }
}

std::vector<std::shared_ptr<A>> getVector() {
    std::vector<std::shared_ptr<A> > aVec{};
    aVec.push_back(std::shared_ptr<A>(getObject()));
    aVec.push_back(std::shared_ptr<A>(getObject()));
    //aVec.push_back(std::shared_ptr<A>(getObject()));
    return aVec;
}

int main()
{
    {
#if 0    
        std::shared_ptr<A> aPtr = nullptr;
        //std::shared_ptr<A> onlyA  = std::make_shared<A>();;
        std::shared_ptr<A> virtualB (getObject());
        //aPtr = getObject();  // not working
        //std::shared_ptr<A> bPtr  = std::make_shared<B>();

        //onlyA->toString();

        //virtualB->toString();
        passRaw(virtualB.get());
        checkNull(virtualB);
        checkNull(aPtr);
        checkNull(std::shared_ptr<A>(new B()));
#endif

        std::vector<std::shared_ptr<A>> vec = getVector();
        for(auto &p: vec) {
            checkNull(p);
        }
    }
   sleep(1);
   return 0;
}

