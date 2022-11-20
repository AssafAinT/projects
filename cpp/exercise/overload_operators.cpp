#include <iostream>
using namespace std;

class X;

int operator+(const X& x1_, const X& x2_)// global operator
{
    return 7;
}

//ostream& operator<<(ostream& os_, const X& x_);

class X
{
public:
    bool operator==(const X& o_) const { return m_a == o_.m_a; }
    //Java style inline – not allowed in our coding standard
private:
    friend ostream& operator<<(ostream& os_, const X& x_);
    int m_a;
};

int main()
{
    X x1; //Type: X side-effect: default ctor generated value - lvalue
    X x2;

    cout<< " x1+x2:" << x1 + x2 << // Type:int side-effect: calling global operator value: rvalue
            " x1==x2:" << (x1 == x2) <<  // Type:bool side-effect: temporary X& generated value: rvalue
            " x1:" << x1 << // Type: ostream& side-effect: /? value: lvalue
            " x2:" << x2 << endl;
    
    return 0;
}

ostream& operator<<(ostream& os_, const X& x_) 
{
    return os_ << x_.m_a;
}