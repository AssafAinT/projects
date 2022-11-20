#include <stdio.h>
#include <assert.h>
void SortArrayOfOneAndZero(int *arr, size_t size);
void PrintArray(int *arr, size_t size);

int main(void)
{
	int arr[10] = {1,0,0,1,1,1,0,0,1,1};
	int arr2[10] = {0,0,0,0,0,0,0,0,0,0};
	int arr3[10] = {1,0,0,0,0,0,0,0,0,1};
	
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
	return (0);
}

void SortArrayOfOneAndZero(int *arr, size_t size)
{
	int *head_ptr = NULL;
	int *tail_ptr = NULL;
	
	assert(NULL != arr);
	
	head_ptr = arr;
	tail_ptr = arr + (size - 1);
	
	while (head_ptr < tail_ptr)
	{
		if ((1 == *head_ptr) && (1 == *tail_ptr))
		{
			--tail_ptr;
		}
		else if ((1 == *head_ptr) && (0 == *tail_ptr))
		{
			*head_ptr = 0;
			*tail_ptr = 1;
			++head_ptr;
			--tail_ptr;
		}
		else if ((0 == *head_ptr) && (0 == *tail_ptr))
		{
			++head_ptr;
		}
		else
		{
			++head_ptr;
			++tail_ptr;
		}
		
	}
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
