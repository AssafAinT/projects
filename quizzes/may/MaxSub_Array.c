#include <stdio.h>

void MaxSubArray(int *arr, size_t size);

static struct max
{
	int min;
	int max;
	int sum;
}curr_max, best_max;

int main()
{
	int array[] = {-2,1,-3,4,-1,2,3,-5,-4};
	
	MaxSubArray(array, 9);
	
	printf("the min index is %d\n", best_max.min);
	printf("the max index is %d\n", best_max.max);
	printf("the sum is %d\n", best_max.sum);
	return (0);
}

void MaxSubArray(int *arr, size_t size)
{
	size_t i=0;
	curr_max.min = 0;
	curr_max.max = 0;
	curr_max.sum = 0;
	
	best_max.min = 0;
	best_max.max = 0;
	best_max.sum = 0;
	
	for (i = 0; i<size; ++i)
	{
		curr_max.sum += arr[i];
		curr_max.max = i;
		
		if(curr_max.sum < 0)
		{
			curr_max.sum = 0;
			curr_max.min = curr_max.max + 1;
		}
		if(best_max.sum < curr_max.sum)
		{
			best_max.min = curr_max.min;
			best_max.max = curr_max.max;
			best_max.sum = curr_max.sum;
		}
	}
}	
	



