#include <stdio.h>
#include <string.h>
#include <stdlib.h>



void ArrayInit(int *arr, int size)
{
    for (int i = 0; i < size; ++i)
    {
        arr[i] = i + 1;
    }
}

int Bingo(void)
{
    static int arr[100] = {0};
    static int size = -1;

    if (size <= 0)
    {
        if (-1 == size)
        {
            size = 100;
            ArrayInit(arr, size);
        }
        size = 100;
    }

    int i = rand() % size;
    int ret = arr[i];
    //swap
    arr[i] = arr[size - 1];
    arr[size - 1] = ret;
    
    --size;

    return ret;
}

int main(void)
{
    for (size_t i = 0; i < 100; ++i)
    {
        printf("%d ", Bingo());
    }
}
