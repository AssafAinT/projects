/****************************************************
* quicksort quiz                                    *
* Assaf Ainhoren                                    *
* Reviewer: Ester Shpoker                           *
* date: 18.07.2022                                  *
****************************************************/
/********************************libraries includes****************************/
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

static void RecQuickSort(int *arr_base, long int start, long int end);

static size_t MakeParti(int *arr_base, long int start,
                        long int piv,long int end);

static void Swap(int *data1, int *data2);

void QuickSort(int *arr_base, size_t size);
void PrintArray(int *arr, size_t size);
int main(void)
{
    int arr[9] = {0, 2, 1, 6, 8, 8, -1, 22, 33};   
    int arr2[9] = {-232, 0, -1, -2222, 8, 12, -1, 22, 33};   
    puts("arr before qsort");
    PrintArray(arr, 9);
    QuickSort(arr, 9);
    puts("arr after qsort");
    PrintArray(arr, 9);
    puts("arr2 before qsort");
    PrintArray(arr2, 9);
    QuickSort(arr2, 9);
    puts("arr2 after qsort");
    PrintArray(arr2, 9);
    return (0);
}
void QuickSort(int *arr_base, size_t size)
{
    assert(NULL != arr_base);
    RecQuickSort(arr_base, 0, size-1);
}
static void RecQuickSort(int *arr_base, long int start, long int end)
{
    if (start < end)
    {
        long int pivot_i = MakeParti(arr_base, start, end, end -1);
        RecQuickSort(arr_base, start, pivot_i-1);
        RecQuickSort(arr_base, pivot_i+1, end);
    }
}

static size_t MakeParti(int *arr_base, long int start,
                        long int piv,long int end)
{
    while (start <=end)
    {
        if (arr_base[start] > arr_base[piv])
        {
            if (arr_base[end] < arr_base[piv])
            {
                Swap(&arr_base[start], &arr_base[end]);
            }
        --end;
        }
        else
        {
            ++start;
        }
    }

    /* change pivot if necessary */
    if (arr_base[start]> arr_base[piv])
    {
        Swap(&arr_base[start], &arr_base[piv]);
        return (start);
    }
    return (piv);
}


static void Swap(int *data1, int *data2)
{
    *data1 = *data1 + *data2;
	*data2 = *data1 - *data2;
	*data1 = *data1 - *data2;
}

void PrintArray(int *arr, size_t size)
{
	size_t index = 0;
	assert(NULL != arr);
	
	
	for ( ; index < size; ++index)
	{
		printf("%d ", arr[index]);
	}
	printf("\n");
}