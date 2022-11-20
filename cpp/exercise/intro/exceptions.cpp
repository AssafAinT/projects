#include <iostream>
#include <exception>
#include <string>
#include <cstdlib>

using namespace std; 
void Foola()
{
    cout<<"Foola"<< endl;
}
class X
{
    public :
    X(){cout<<"X Ctor "<< endl;}
    ~X(){cout<<"X Dtor "<< endl;}
};

struct BadDog: public runtime_error 
{   
    BadDog(const string& s_ = "This is a bad dog"): runtime_error(s_) {} 
}; 

void Fifi() throw(int , double, const char *)
{ 
    // throw BadDog("bad pup"); cerr << "Fifi() after throw" << endl; 
    throw "abanibi abotebe";
} 
void Foo() 

{ 
    X x1;     
    Fifi();     
    cerr << "Foo() after Fifi()" << endl; 
} 

void Bar() 
{ 
    Foo(); 
    cerr << "Bar() after Foo()" << endl; 
} 

void InalDInak()
{
    cerr << "InalDInak() after Bar()" << endl; 
    exit (-1);
}
int main()
{ 
    Bar();    
    set_terminate(InalDInak);

    // try     
    // {         
    //     Bar();     
    // }     
    // catch(bad_alloc&)     
    // {         
    //     cerr << "Out of memory! exiting."; exit(2);     
    // }
    // catch(BadDog& b)     
    // {         
    //     cerr << "Bad dog exception: " << b.what(); exit(3);     
    // }     
    // catch( exception& r )
    // {
    //     cerr << "unknown exception: " << r.what();
    //     exit(4);     
    // }     
    // catch( ... )
    // {
    //     cerr << "unknown exception dot dot dot " << endl;
    //     exit(4);     
    // }     
    return 0; 
}