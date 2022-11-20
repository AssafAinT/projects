#include <stddef.h>
#include <stdio.h>
#define SIZE_T_BITS 64

size_t RotateLeft(size_t num, size_t num_of_rotations)
{
    return (num << num_of_rotations | num >> SIZE_T_BITS - num_of_rotations);
}

unsigned char RotateLeftChar(unsigned char num, size_t num_of_rotations)
{
    return (num << num_of_rotations | num >> 8 - num_of_rotations);
}

int main(void)
{
    printf("%ld\n",RotateLeft(13,2 ));
    printf("%d\n",RotateLeftChar(129,2 ));

    return 0;

}