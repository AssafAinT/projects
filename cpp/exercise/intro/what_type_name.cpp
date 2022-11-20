#include <iostream>

using namespace std;

int main (void)
{
    const int i;
    int const i;
    int const* i;
    struct X* const p;
    struct X const x1;
    const struct X *p;
    const struct X * const p;
    int const* (* const f)(int*)= foo;
}