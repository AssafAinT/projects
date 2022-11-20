#include <stdio.h>
#include <assert.h>
#include <limits.h>
size_t CountSetBits(unsigned long int number);
size_t CountSetBitsRecursive(unsigned long int number, size_t *o_counter);
int main(void)
{
    unsigned long int number = 1;
    unsigned long int number1 = 16;
    unsigned long int number2 = 17;
    unsigned long int number3 = 33;
    size_t loop_counter =0;
    assert(1 == CountSetBits(number)); 
    assert(1 == CountSetBits(number1));
    assert(2 == CountSetBits(number2));
    assert(2 == CountSetBits(number3));

    CountSetBitsRecursive(number3, &loop_counter); 
    assert(2 == loop_counter);
    loop_counter = 0;
    CountSetBitsRecursive(number2, &loop_counter); 
    assert(2 == loop_counter);

    return 0;
}

size_t CountSetBits(unsigned long int number)
{
    size_t count = 0;
    assert(ULONG_MAX >= number);
    for (  ; 0 < number; number &= (number -1))
    {
        ++count;
    }
    return (count);
}

size_t CountSetBitsRecursive(unsigned long int number, size_t *o_counter)
{
    if (0 == number)
    {
        return (*o_counter);
    }
    ++*o_counter;
    return(CountSetBitsRecursive(number &= (number -1), o_counter));
}
