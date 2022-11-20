#include <stdio.h>
#include <assert.h>
#define FAIL_TO_LOCATE -1 
int BsArray(int *arr, size_t size, int data_to_find);
int main(void)
{
	int arr[8] = {1, 2, 5, 6, 8, 12, 22, 33};
	int arr2[9] = {0, 2, 5, 6, 8, 12, 18, 22, 33};
	assert(-1 == BsArray(arr, 8, 3));
	assert(2 == BsArray(arr, 8, 5));
	assert(0 == BsArray(arr, 8, 1));
	
	assert(0 == BsArray(arr2, 9, 0));

	return (0);
}

int BsArray(int *arr, size_t size, int data_to_find)
{
	int lowest = 0;
	int highest = size - lowest;
	int found = 0;
	assert(NULL != arr);
	
	while (lowest <= highest)
	{
		found = (lowest + highest) / 2;
		
		if (arr[found] == data_to_find)
		{
			return (found);
		}
		if (arr[found] < data_to_find)
		{
			lowest += found;
		}
		else
		{
			highest = found - lowest;
		}
	}
	
	return (FAIL_TO_LOCATE);
}

