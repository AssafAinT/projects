#include <iostream>

class X
{
public:
    X(double d_) :m_a(d_) {std::cout << "X Ctor " << d_ << "\n";}
    virtual ~X() {std::cout << "X Dtor\n";}
    
private:
    double m_a;
};

class Y: public X
{
public :
    Y(double d_, int i_) :  X(d_), m_b(i_){std::cout << "Y Ctor " << d_ << " | " << i_ << "\n";}
    ~Y() {std::cout << "Y Dtor\n";}

private:
    int m_b;
};

int main(void)
{
    Y y1(0.0, 0), y2(14.2, 5);
    Y y3(0.0, 0), y4(14.2, 5);

    X &x1 = y1;
    X &x2 = y2;

    x1 = x2;
    y3 = y4;
    
    Y& yy = static_cast<Y&>(x1);

    return 0;
}