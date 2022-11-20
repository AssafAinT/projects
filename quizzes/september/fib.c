/****************************************************
* fibonacci                                         *
* Assaf Ainhoren                                    *
* Reviewer: Ester Shpoker                           *
****************************************************/
/********************************libraries includes****************************/
#include <stdio.h>
#include <assert.h>

static const int first_elem = 1;

int Fib(int elem_i);
int FibIter(int elem_i);

int main(void)
{
    assert(Fib(0) == 0);
    assert(FibIter(0) == 0);
    assert(Fib(2) == 1);
    assert(FibIter(2) == 1); 
    assert(Fib(3) == 2);
    assert(FibIter(3) == 2);
    assert(Fib(45) == 1134903170);
    assert(FibIter(45) == 1134903170);
    return (0);
}

int Fib(int elem_i)
{
    if ( first_elem >= elem_i )
    {
        return elem_i;
    }
    return (Fib(elem_i-1) + Fib(elem_i -2));
}
int FibIter(int elem_i)
{
    int runner = 3;
    int fib_1 = 0;
    int fib_2 = 1;
    int fib_n = fib_1 + fib_2;

    if (0 == elem_i)
    {
        return 0;
    }

    for ( ; runner <= elem_i; ++runner)
    {
        fib_1 = fib_2;
        fib_2 = fib_n;
        fib_n = fib_1 + fib_2;
    }
    return (fib_n);
}
