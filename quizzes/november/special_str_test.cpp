#include <iostream>
#include "special_string.hpp"
using namespace std;
using namespace ilrd;
int main(void)
{
    String s1("1234");
    s1 = '@';

    cout << s1 << endl;

    String s2("ABCD");
    cout << String::GetInstance() << endl;

    s2[0] = 'D';
    cout << s2 << endl;
    String s3 = "Abada";
    cout << s3 << endl;


    s3[0] = s2[0];

    cout << s3 << endl;
    s3 = s2 = s1;




}