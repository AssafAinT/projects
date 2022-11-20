#include <iostream>

#include "some_funcs.hpp"
using namespace std;
extern "C"
{
    int Bla(int a, int b, int c)
    {
        cout << " you entered " << a << " " << b << " " << c << endl;
        cout << " the result is " << a * b * c << endl;

        return (a * b * c);

    }
    char UpperC(char c )
    {
        return (c - 32);
    }

}