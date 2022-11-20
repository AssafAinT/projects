#include <iostream>
#define UNUSED(param) (void)param
using namespace std;

class X;

int operator+(const X& x1_, const X& x2_)
{
    UNUSED(x1_);
    UNUSED(x2_);
    return 7;
}

ostream& operator<<(ostream& os_, const X& x_);
bool operator==(const X& x_,const X& o_);
bool operator<(const X& x_,const X& o_);
bool operator>(const X& x_,const X& o_);

class X
{
public:
    int Cma() const;
private:
    int m_a;
};

int main()
{
    X x1;
    X x2;

    cout<< " x1+x2:" << x1 + x2 <<
            " x1==x2:" << (x1 == x2) <<
            " x1:" << x1 <<
            " x2:" << x2 <<
            " x1 < x2 :" << (x1 < x2) <<
            "  x1 > x2: " << (x1 > x2) << endl;
    
    return 0;
}
bool operator==(const X& x_,const X& o_)
{
    return x_.Cma() == o_.Cma(); 
}
ostream& operator<<(ostream& os_, const X& x_) 
{
    return os_ << x_.Cma();
}
bool operator<(const X& x_,const X& o_)
{
    return x_.Cma() < o_.Cma(); 
}
bool operator>(const X& x_,const X& o_)
{
    return x_.Cma() > o_.Cma(); 
}
int X::Cma() const
{
    return m_a;
}