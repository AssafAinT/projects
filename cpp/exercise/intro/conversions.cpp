#include <iostream>

class X
{
public:
    explicit X();
    X(int a_);
    explicit X(int a_, int b_);

    operator int() const;
    void Print() const;

private:
    int m_num; // so int() operator can be used 
}; 

X::X() : m_num(0) { }
X::X(int a_) : m_num(a_) { }
X::X(int a_, int b_) : m_num(a_ + b_) { }

X::operator int() const 
{ 
    return m_num;
}

void X::Print() const
{ 
    std::cout << "X::Print() " << m_num << std::endl;
}

void Fifi(X x_)
{
    std::cout << "Fifi() " << x_ << std::endl;

    x_.Print();
}

X CreateObjet(int x);
int main()
{
    X x1(97);
    int m = x1;
    Fifi(x1);     // (1)
    Fifi(X(97));   // (2)
    Fifi(CreateObjet(97)); // another way
    Fifi(9);      // (3)
    Fifi(X(12, 4)); // (4)
    std::cout << "m " << m << std::endl;
    return x1 * 3; //(5)
}

X CreateObjet(int x)
{
    return (x);
}