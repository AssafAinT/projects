#include "complex.hpp"
#include <iostream>
using namespace ilrd;
int main(void)
{
    Complex x1(2, 3);
    Complex x2(2, 3);
    Complex x3(2, 3);
    Complex x4(2, 3);
    Complex x5(3, -8);
    Complex x6(4, -2);
    Complex x7;
    std::cout << x1 << " = x1" << std::endl;
    std::cout << x2 << " = x2" << std::endl;
    std::cout << (x1 + x2) << " = x1 + x2" << std::endl;
    std::cout << (x1 + x2 + x3 + x4) << " = x1 + x2 + x3 + x4" << std::endl;
    std::cout << (x1 - x2) << " = x1 - x2" << std::endl;
    std::cout << (x1 == x2) << " = x1 == x2" << std::endl;
    std::cout << (x1 != x2) << " = x1 != x2" << std::endl;
    std::cout << (x1 * x2) << " = x1 * x2" << std::endl;
    std::cout << (x1 / x2) << " = x1 / x2" << std::endl;
    std::cout << (x1 += x2) << " = x1 += x2" << std::endl;
    std::cout << (x1 -= x2) << " = x1 -= x2" << std::endl;
    std::cout << (x1 *= x2) << " = x1 *= x2" << std::endl;
    std::cout << (x5 *= x6) << " = x5 *= x6" << std::endl;
    std::cout << (x1 /= x2) << " = x1 /= x2" << std::endl;
    std::cin >> x7;
    std::cout << x7 << " = x7" << std::endl;
    std::cout << (x1 != x7) << " = x1 != x7" << std::endl;
    size_t cntr = 100000000;
    while (0 != cntr)
    {
        (x1 + x2);
        --cntr;
    }

    return 0;
}