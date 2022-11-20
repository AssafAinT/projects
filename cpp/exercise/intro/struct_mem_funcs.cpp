#include <iostream>
struct X
{
    X(int a_, int b_);

    void Inc();
    void Dec();

    int m_a;
    int m_b;
};

X::X(int a_, int b_): m_a(a_), m_b(b_)
{}

void X::Inc()
{
    std::cout << "this:" << this <<std::endl; 
    ++m_a;
    ++m_b;
}

void X::Dec()
{
    std::cout << "this:" << this <<std::endl; 
    --(this->m_a);
    --m_b;
}

void Inc()
{
}

int main()
{
    X x1(7 ,55);
    X x2(x1);

    Inc();
    x1.Dec();
    x1.Inc();
    x2.Dec();

    std::cout << " The size of X is " << sizeof(x2) << std::endl;
    return 0;
}