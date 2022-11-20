#include<cstdio>
#include<iostream>
// struct X
// {
// /*public:*/
    // X();
    // explicit X(int a_);
    // void Foo();
    // void Hacker(int x_);
    // int m_b;
// private:
    // X& operator=(const X& other_);
    // int m_a;
// };

class X
{
public:
    X();
    explicit X(int a_);
    void Foo();
    void Hacker(int x_);
    int HackerV(void);
    int m_b;
private:
    X& operator=(const X& other_);
    int m_a;
};

X::X() : m_b(0)
{
    printf("default constructor\n");
}

X::X(int a_)
    : m_a(a_)
{
}

X& X::operator=(const X& other_)
{
    m_a = other_.m_a;
    // m_b = other_.m_b;

    std::cout << "this:" << this <<
        " X assignment operator. m_a:" << m_a <<
        " does not change m_b:" << m_b << std::endl;

    return *this;
}
void X::Foo()
{
    printf("%d\n",m_a);
}
void X::Hacker(int x_)
{
    m_a = x_;
    printf("changed m_a indirectly %d\n",m_a);
    
} 

int X::HackerV(void)
{
    return(m_a);    
}
void Foo(const X &x_)
{
    printf("%d\n",x_.m_b);
    //printf("%d\n",x_.m_a);
}


int main()
{
    X x1;
    X x2(258);

    x1.Foo();
    printf("%d\n", x1.m_b);
    //printf("%d\n", x1.m_a);
    Foo(x1);
    x1.Hacker(12);
    printf("%d is private m_a\n", x1.HackerV());
    
    return 0;
}
