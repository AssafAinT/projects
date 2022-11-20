#include <iostream>
#include "classical_string.hpp"

using namespace std;
using namespace ilrd;
int main(void)
{
    String s1("aaa");
    String s2 = "bbb";
    String s3(s2);
    String s4;

    s4 = s2;
    s3[2] = 'k';
    cout << s3 << endl;


}