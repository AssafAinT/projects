#include <iostream> // std::cout, std::cin

#include "rc_string.hpp"

using namespace std;
using namespace ilrd;

RCString foo(RCString s)
{
    RCString s2(s);
    
    return s2;
}

int main(void)
{
    RCString s1("hello world");
    s1 = "1234121";

    cout << s1 << endl;

    s1[0] = 'a';
    cout << s1 << endl;

    const RCString s2 = s1;

    cout << s1[0] << endl;

    RCString s3;
    cin >> s3;
    cout << "using << operator s7 is:" << s3 << endl;

    RCString rcs1("123");
    RCString rcs2("1234");

    cout << rcs1.Length() << endl;
    cout << (rcs1.Length() == rcs2.Length())<< endl;
    cout << (rcs1.Length() < rcs2.Length())<< endl;
    cout << (rcs1.Length() > rcs2.Length())<< endl;
    
    rcs1 = rcs2;

    cout << rcs1.Length() << endl;
    cout << (rcs1.Length() == rcs2.Length())<< endl;
    cout << (rcs1.Length() < rcs2.Length())<< endl;
    cout << (rcs1.Length() > rcs2.Length())<< endl;
    cin >> rcs1;
    cout << rcs1.Length() << endl;
    cout << rcs1 << endl;
    rcs1[1] = 'r';
    cout << rcs1 << endl;
    
    
    RCString str1 = "123";
    RCString str2;
    str2 = foo(str1);
}
