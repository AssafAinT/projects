#include "cpp_bit_array.hpp"
#include <iostream>
using namespace std;
using namespace ilrd;
int main(void)
{
    BitArray b1;
    BitArray b2;
    b1[2] = true;
    int i = 3;
    if (b1[2])
    {
        cout << "b1 is set" << endl;
    }
    b2[0] = false;
    if (b2[0])
    {
        cout << "b2 is set on 0" << endl;
    }
    else
    {
        cout << "b2 is off" << endl;
    }
    b1[i] = true;
    b2[i] = b1[i];
    if (b2[i])
    {
        cout << "b2 is set on " << i << endl;
    }
    else
    {
        cout << "b2 is off" << endl;
    }


    //b1[0] = true;
}