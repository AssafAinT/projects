/****************************************************
* insertion_sort                                    *
* Assaf Ainhoren                                    *
* Reviewer: Ester Shpoker                           *
* date: 18.07.2022                                  *
****************************************************/
/********************************libraries includes****************************/
#include <stdio.h> /* printf, size_t */
#include <assert.h> /* assert */
#include <string.h> /* memmove */

void InsertionSort(int *arr, size_t size);
void InsertSortedArray(int *arr, size_t size, int num_to_insert);
void PrintArray(int *arr, size_t size);

int main(void)
{
    int arr[10] = {1 , 9, 8, 4, 7, 3, 2, 6, 5 , 4};
    puts("before insertion sort");
    PrintArray(arr, 10);
    puts("after insertion sort");
    InsertionSort(arr, 10);
    PrintArray(arr, 10);
    return (0);
}

void InsertionSort(int *arr, size_t size)
{
    size_t i = 1;
    
    for ( ; i < size; ++i)
    {
        if (arr[i] < arr[i - 1])
        {
            InsertSortedArray(arr, i, arr[i]);
        }
    }
}

void InsertSortedArray(int *arr, size_t size, int num_to_insert)
{
    size_t i = 0;

    for ( ; arr[size] > arr[i]; ++i)
    {
        /* empty for loop */
    }
    memmove(&arr[i + 1], &arr[i], (size -i)*(sizeof(int)));
    arr[i] = num_to_insert;
}

void PrintArray(int *arr, size_t size)
{
    size_t i = 0;

    printf("[");
    for ( ; i < size; ++i)
    {
        printf("%d |", arr[i]);
    }
    printf("]\n");
}