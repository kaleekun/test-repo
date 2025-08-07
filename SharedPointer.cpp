// Author: KaLee
#include<iostream>
using namespace std;

class A {
public:
    A() { cout << "constructed" << endl; }
    ~A() { cout << "destructed" << endl; }
};

template<typename T>
class SP {
public:
    SP(T* ptr= NULL) :p_ptr(ptr), refCount(nullptr) {
        if (p_ptr) {
            refCount = new int;
            *refCount = 0; ++(*refCount);
        }
    }
    ~SP() {
        if (refCount) {
            --(*refCount);
            if (*refCount == 0) {
                delete refCount;
                delete p_ptr;
            }
        }
    }
    int GetRefCount() { return (*refCount); }
    SP& operator=(const SP& sp) {
        if (this == &sp) return *this; // do nothing
        if (this->refCount) {
            --(*(this->refCount));
            if (*(this->refCount) == 0) {
                delete this->refCount; this->refCount = nullptr;
                delete this->p_ptr; this->p_ptr = nullptr;
            }
        }
        this->p_ptr = sp.p_ptr;
        if (this->p_ptr) {
            this->refCount = sp.refCount;
            ++(*(this->refCount));
        }
    }
    SP(const SP& sp) {
        this->p_ptr = sp.p_ptr;
        if (this->p_ptr) {
            this->refCount = sp.refCount;
            ++(*(this->refCount));
        }
    }
private:
    T* p_ptr;
    int* refCount;
};

int main()
{
    {
        auto a = SP<A>(new A);
        cout << a.GetRefCount() << endl;
        {
            SP<A> b = SP<A>(new A);
            b = a;
            cout << a.GetRefCount() << endl;
        }
        cout << a.GetRefCount() << endl;
    }
    return 0;
}
