/****************************************************
* two_sum_quiz                                      *
* Assaf Ainhoren                                    *
* Reviewer: Ester Shpoker                           *
* date: 18.07.2022                                  *
****************************************************/
/********************************libraries includes****************************/
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

/* in case target not found the o_arr will stay empty */

void TwoSum(int *arr, size_t size, int target, int *o_arr);
void TwoSumUsingSort(int *arr, size_t size, int target, int *o_arr);
static int GoodCmp(const void *a, const void *b);

int main(void)
{
    int arr[] = {0, -1, 2, -3, 1};
    int tar_arr[2] = {0};
    int arr2[] = {0, -1, 2, -3, 1};
    int tar_arr2[2] = {0};
    size_t i = 0;
    TwoSum(arr, 5, -2, tar_arr);

    printf("[ ");
    for ( ; i < 2; ++i)
    {
        printf("%d | ", tar_arr[i]);
    }
    printf("]\n ");

    TwoSumUsingSort(arr2, 5, 2, tar_arr2);

    printf("[ ");
    for (i=0 ; i < 2; ++i)
    {
        printf("%d | ", tar_arr2[i]);
    }
    printf("]\n ");
    return (0);
}

void TwoSum(int *arr, size_t size, int target, int *o_arr)
{
    size_t i = 0;
    size_t j = 0;
    int is_found = 0;

    for ( ; i < size - 1; ++i)
    {
        for ( j = i + 1; j < size && !is_found; ++j)
        {
            if (arr[i] + arr[j] == target)
            {
                o_arr[0] = i;
                o_arr[1] = j;
                is_found = 1;
            }
        }
    }
}

void TwoSumUsingSort(int *arr, size_t size, int target, int *o_arr)
{
    size_t head = 0;
    size_t tail = size - 1;
    int is_found = 0;

    qsort(arr, size, sizeof(int), GoodCmp);

    while (head < tail && !is_found)
    {
        if (arr[head] + arr[tail] == target)
        {
            o_arr[0] = head;
            o_arr[1] = tail;
            is_found = 1;
        }
        if (arr[head] + arr[tail] < target)
        {
            ++head;
        }
        else
        {
            --tail;
        }
    }

}

static int GoodCmp(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}