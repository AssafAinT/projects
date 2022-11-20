#include <iostream> // std::cout
#include "structs.hpp"
Y::Y(): m_x(X()), m_i(4)
{
    // m_a = 3;
    // m_b = 4;
    std::cout << "This:"<< this <<
    " Y default Ctor. m_a :" << m_x.m_a <<
    " m_i: " << m_i << std::endl; 
}
X::X(): m_a(3), m_b(4) // implementing the default ctor
{
    // m_a = 3;
    // m_b = 4;
    std::cout << "This:"<< this <<
    " X default Ctor. m a :" << m_a <<
    " m_b: " << m_b << std::endl; 
}

X::X(int a_, int b_): m_a(a_), m_b(b_) //Implementation of second Ctor
{
    std::cout << "This:"<< this <<
    " X int int Ctor. m a :" << m_a <<
    " m_b: " << m_b << std::endl; 
}

X::X(const X& other_): m_a(other_.m_a), m_b(other_.m_b) //Implementation of of copy ctor
{
    std::cout << "This:"<< this <<
    " X copy Ctor. m a :" << m_a <<
    " m_b: " << m_b << std::endl; 
}

// Y::Y(const Y& other_): m_i(other_.m_i) //Implementation of of copy ctor
// {
// 
// }

X& X::operator=(const X& other_)
{
    m_a = other_.m_a;
    // m_b = other_.m_b;

    std::cout << "this:" << this <<
        " X assignment operator. m_a:" << m_a <<
        " does not change m_b:" << m_b << std::endl;

    return *this;
}
Y& Y::operator=(const Y& other_)
{
    m_i = other_.m_i;
    m_x.m_a = other_.m_x.m_a;
    // m_b = other_.m_b;

    std::cout << "this:" << this <<
        " Y assignment operator. m_i:" << m_i  <<
        " m_x.m_a :" << m_x.m_a <<
        " does not change m_b:" << m_x.m_b << std::endl;

    return *this;
}
X::~X()
{
    std::cout << "this:" << this <<
        " X destructor. m_a:" << m_a <<
        " m_b:" << m_b << std::endl;
}