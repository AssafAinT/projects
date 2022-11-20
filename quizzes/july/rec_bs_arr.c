#include <stdio.h>
#include <assert.h>
#define FAIL_TO_LOCATE -1 
int RecBsArray(int *arr,int num_to_find, size_t start_ind, size_t last_elem);
int BsArray(int *arr,int data_to_find, size_t size);
int main(void)
{
	int arr[8] = {1, 2, 5, 6, 8, 12, 22, 33};
	int arr2[9] = {0, 2, 5, 6, 8, 12, 18, 22, 33};
	
	assert(4 == BsArray(arr, 8,7));
	assert(-1 == BsArray(arr, 23,7));
	assert(0 == BsArray(arr2, 0,8));
	assert(8 == BsArray(arr2,33,8));
	

	return (0);
}
int BsArray(int *arr,int data_to_find, size_t size)
{
	return(RecBsArray(arr, data_to_find, 0, size));
}

int RecBsArray(int *arr,int num_to_find, size_t start_ind, size_t last_elem)
{
	int mid = (start_ind + last_elem) / 2;
	
	if (start_ind > last_elem)
	{
		return (FAIL_TO_LOCATE);
	}
	
	if (num_to_find == arr[mid])
	{
		return (mid);
	}
	else if (num_to_find > arr[mid])
	{
		start_ind = mid + 1;
	}
	else
	{
		last_elem = mid - 1;
	}
	return(RecBsArray(arr, num_to_find, start_ind, last_elem ));
}
