#include <iostream>
#include <exception>
#include <string>
#include <cstdlib>
#include <typeinfo>
#include <cstdio>
using namespace std;
int Foo(int) throw(bad_alloc);

void Bar() throw(int, bad_cast);

class X
{
    public :
    X(){cout<< this << endl;cout<<"X Ctor "<< endl;}
    ~X();
};

X::~X()
{   
    cout<< this << endl;  
    cout<<"X Dtor "<< endl;
    cerr << Foo(12) << endl;
}

void Fishi()
{
    X x1;
    Bar();
    //try
    //{
    //    X x1;
    //    Bar();
    //}
    //catch(exception& e)
    //{
    //    cerr << "exception cout. what:" << e.what() << endl;
    //}
    
}
int main()
{
    Fishi();
    // try
    // {
        // X x1;
        // Fishi();
    // }
    // catch(exception& e)
    // {
        // cerr << "exception cout. what:" << e.what() << endl;
    // }
    
    //Foo(12); 
    return 0;
}

int Foo(int) throw(bad_alloc)
{
    throw bad_alloc();
    return 0;
}

void Bar() throw(int, bad_cast)
{
    //throw bad_cast();
}
