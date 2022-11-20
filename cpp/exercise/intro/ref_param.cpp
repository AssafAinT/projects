#include <iostream> // std::cout

void Foo(const double&);
void Bar(double&);

int main(void)
{
    int i = 0;
    int j =0;
    Foo(i);
    Bar(reinterpret_cast<double &>(j));
    std::cout << &i << std::endl;
    std::cout << &j << std::endl;
}

void Foo(const double& cd)
{   
    std::cout << &cd << std::endl;
}
void Bar(double& d)
{
    std::cout << &d << std::endl;
}