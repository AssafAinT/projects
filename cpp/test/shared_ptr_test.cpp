#include <iostream>
#include "shared_ptr.hpp"
using namespace std;
using namespace ilrd;
class A
{
    int a;
};
class B : public A
{
    int b;
    public:
    void foo()
    {
        cout << "foo" << endl;
    }
};

int main(void)
{
    SharedPtr<int> first_one(new int(12));
    SharedPtr<int> pp = first_one;
    SharedPtr<int> q(first_one);
    // int x= 12;
    // SharedPtr<int> xptr(&x);
    SharedPtr<B> xptr(new B);
    SharedPtr<A> xptr2 = xptr;
    

    xptr->foo();
    q = first_one;
    SharedPtr<int> ptr1(new int(151));
    cout << "--- Shared pointers ptr1 ---\n";
    *ptr1 = 100;
    cout << " ptr1's value now: " << *ptr1 << endl;
    cout << ptr1;

    SharedPtr<int> ptr2 = ptr1;
    cout << "--- Shared pointers ptr1, ptr2 ---\n";
    cout << ptr1;
    cout << ptr2;

    SharedPtr<int> ptr3(ptr2);
    cout << "--- Shared pointers ptr1, ptr2, ptr3 "
            "---\n";
    cout << ptr1;
    cout << ptr2;
    cout << ptr3;

    cout << "--- Shared pointers ptr1, ptr2 ---\n";
    cout << ptr1;
    cout << ptr2;

    cout << "--- Shared pointers ptr1 ---\n";
    cout << ptr1;
    cout << *ptr1 << endl;
    cout << *ptr2 << endl;
    cout << *ptr3 << endl;
    
    return 0;
}