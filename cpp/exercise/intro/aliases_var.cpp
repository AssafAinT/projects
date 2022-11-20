#include <iostream>

using namespace std;
static int& FiguringOutAliases(int number);
static void Aliases(int& x);
int main(void)
{
    int i = 8;
    int& ip = i;
    ip = 9;
    cout<< i << endl;

    double j = 12.123;
    double& jp = j;
    jp = 23431.123;
    cout<< j << endl;

    ip = FiguringOutAliases(12);
    cout<< i << endl;

    cout<< sizeof(ip) << endl;
    cout<< sizeof(jp) << endl;
    cout<< &ip << endl;
    cout<< &i << endl;

    Aliases(ip);
    cout<< i << endl;
}

static int& FiguringOutAliases(int number)
{
    int &to_ret = number;
    to_ret++; 
    return (to_ret);
}

static void Aliases(int& x)
{
    ++x;
}