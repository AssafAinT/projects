#include <iostream> // std::cout
#include "overload_vs_template.hpp"
int main(void)
{
    foo(4.2);
    foo(5);
    foo<int>(5);
    foo<size_t>(5);
    return 0;
}