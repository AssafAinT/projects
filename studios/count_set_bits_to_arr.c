#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>


int CountSetBits(int n);
int* countBits(int n, int* returnSize);
int main(void)
{
    int* returnSize = malloc(sizeof(int) * 1);
    int *ret = countBits(8, returnSize);

    for (int i = 0; i <= 8 ; ++i)
    {
        printf("%d\n", ret[i]);      
    }

    free(returnSize);
    free(ret);
    return 0;
}

int* countBits(int num, int* returnSize)
{
    num++;
    *returnSize = num;
    int* arr = (int*)malloc(sizeof(int)*num);
    arr[0] = 0;
    
    for(int i = 1; i < num; ++i)
    {
        arr[i] = CountSetBits(i);
    }
    
    return arr;
}

int CountSetBits(int n)
{
    size_t counter = 0;
    while (n)
    {
        ++counter;
        n &= n -1;
    }
    return counter;
}
