#include <stdio.h> /*printf */
#include <assert.h> /* assert */

#define SIZE_OF_ARR_TO_SEND(arr) (sizeof(arr))/(sizeof(int))
/* the function returns the missing number in a un sorted sequence */
int FindMissingNum(int *arr, size_t arr_size);

int main(void)
{
	int arr[]= {1,4,5,3,2,6};
	
	size_t size = SIZE_OF_ARR_TO_SEND(arr);
	int miss_num = FindMissingNum(arr, size);
	
	printf("The missing Number is: %d\n", miss_num);
	return (0);
}

int FindMissingNum(int *arr, size_t arr_size)
{
	/* finding the sum of the sequence */
	int missing_num = 0;
	size_t index = 0;
	
	assert(1 < arr_size );
	
	missing_num = (((arr_size +1) * (arr_size +2)) / 2);
	
	for ( ; index < arr_size; ++index)
	{
		missing_num -= arr[index];
	}
	
	return (missing_num);
}


