#include <stdio.h>
#include <assert.h>
void SortArrayOfOneAndZero(int *arr, size_t size);
void SortArrayOfOneAndZeroTwoPointers(int *arr, size_t size);
void BubbleSort(int *arr, size_t size);
void Swap(int *x, int *y);
void PrintArray(int *arr, size_t size);

int main(void)
{
	int arr[10] = {1,0,0,1,1,1,0,0,1,1};
	int arr2[10] = {0,0,0,0,0,0,0,0,0,0};
	int arr3[10] = {1,0,0,0,0,0,0,0,0,1};
    int arr4[10] = {1,0,1,0,1,0,0,0,0,1};
	
	printf("first check\n\n");
	PrintArray(arr, 10);
	SortArrayOfOneAndZero(arr, 10);
	PrintArray(arr, 10);
	printf("\nsecond check\n\n");
	PrintArray(arr2, 10);
	SortArrayOfOneAndZero(arr2, 10);
	PrintArray(arr2, 10);
	printf("\nthird check\n\n");
	PrintArray(arr3, 10);
	SortArrayOfOneAndZero(arr3, 10);
	PrintArray(arr3, 10);
    printf("\nfourth check\n\n");
	PrintArray(arr4, 10);
    SortArrayOfOneAndZeroTwoPointers(arr4, 10);
	PrintArray(arr4, 10);

	return (0);
}
void SortArrayOfOneAndZeroTwoPointers(int *arr, size_t size)
{
    int *head = arr;
    int *tail = arr + (size -1);

    while (head < tail) 
    {
        if (*head == 1 && *tail ==0)
        {
            Swap(head, tail);
            ++head;
            --tail;
        }
        if (*head == 0)
        {
            ++head;
        }
        if (*tail == 1)
        {
            --tail;
        }
    }
}

void SortArrayOfOneAndZero(int *arr, size_t size)
{
    assert(NULL != arr);
	BubbleSort(arr, size);
}
void BubbleSort(int *arr, size_t size)
{
	size_t i = 0;
	size_t k = 0;
	int is_sorted = 0;
	
	for ( ;i < size && !is_sorted; ++i)
	{
		is_sorted = 1;
		for ( k = 0 ; k < (size - i - 1); ++k)
		{
            if (arr[k] >arr[k + 1])
            {
                Swap(&arr[k] , &arr[k + 1]);
                is_sorted = 0;
            }
        }
	}
}


void Swap(int *x, int *y)
{
	*x = *x + *y;
	*y = *x - *y;
	*x = *x - *y;
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
