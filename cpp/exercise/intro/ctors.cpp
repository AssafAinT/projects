/****************************************************
* codelines                                         *
* Assaf Ainhoren                                    *
* Reviewer: Herscho the king                        *
* date: 11.09.2022                                  *
****************************************************/
/********************************libraries includes****************************/
#include <iostream>
#include "structs.hpp"
int main(void)
{
    X x1;
    X x2(2);
    X *px = new X(x2);
    X x3(9, 10);
    X x4(x1); 
    x1 = x3;
    std::cout << " The size of X is " << sizeof(x3) << std::endl;
    delete px; px = 0;
    X *xp = new X[10];
    delete[] xp;
    Y y1;
    std::cout << " y1.mi = " << y1.m_i << std::endl;
    y1.m_x.m_a = 250;
    //y1.m_x.m_b = 750;
    Y y2(y1);
    Y y3;
    y3 = y1;

    return (0);
}