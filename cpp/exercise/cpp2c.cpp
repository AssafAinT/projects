#include <iostream> // std::cout
using namespace std;
class B
{
    int i;
};
union u_a 
{
    struct foo : public B { };
    char a;
    unsigned int i;
    float size;
    void Print();
};
void u_a::Print()
{
    cout << this->i << endl;
}

int main(void)
{
struct A
{

};

struct B
{
    int x;
    int y;
};  

    //cout << sizeof(struct A)<< endl;
    //cout << sizeof(struct B)<< endl;
    u_a a{12};
    a.Print();
    int *arr = new int[12];
    delete arr;
    return 0;
}