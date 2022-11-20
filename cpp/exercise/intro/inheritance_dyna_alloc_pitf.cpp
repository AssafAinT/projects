#include <iostream>
using namespace std;
class X
{
public:
    X() {cout<<"x ctor"<<endl;cout<<this<<endl;}
   virtual ~X() {cout<<"x dtor"<<endl;cout<<this<<endl;}

private:
    int m_a;
};

class Y: public X
{
public:
    Y() {cout<<"y ctor"<<endl;cout<<this<<endl;}
    ~Y() {cout<<"y dtor"<<endl;cout<<this<<endl;};
private:
    int m_b;
};

int main()
{
    X *xp= new Y[2];

    delete[] xp;

    return 0;
}