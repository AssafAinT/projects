#include <iostream> // std::cout

class X
{
public:
    X() : m_id(++s_cntr) {}
    int GetId() { std::cout << m_id << std::endl; return m_id;}
    static void PrintHello();
private:
    int m_id;
    static int s_cntr;
};

int X::s_cntr = 7;
void X::PrintHello()
{
    std::cout << "Hello " << std::endl;
}
int main()
{
    X x1;
    X x2;
    X::PrintHello();
    x1.GetId();
    x2.GetId();
    return 0;   
}