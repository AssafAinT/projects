#include <iostream>
#include "overload_vs_template.hpp"
template<typename T>
void foo(T t)
{
    std::cout << t << " Generic foo for " << typeid(t).name() << std::endl;
}

template <>
void foo<int>(int t)
{
    std::cout << t << " Specialized foo (for int param)\n";
}
// Explicit instantiation
template void foo<double>(double);
template void foo<size_t>(size_t);