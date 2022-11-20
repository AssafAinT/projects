#include <stdio.h>

unsigned int add_binary(unsigned int x, unsigned int y)
{
    while ( 0 != y )
    {
        unsigned int carry = x & y; //check if two bit on
        x = x ^ y; // 
        y = carry << 1;
    }

    return x;
}
int main ()
{
    unsigned int x = 12;
    unsigned int y = 25;
    unsigned int z = add_binary(x, y);

    printf("%d\n", z);

    return 0;
}