#include <stdio.h>
void FindTwoMissingNums(unsigned int *arr, size_t size, unsigned int *res_arr);
void FindTwoMissingNumsByXor(unsigned int *arr, size_t size);
int main()
{
	unsigned int arr[4] = {1,2,5,6};
	unsigned int result_arr[2] = {0};
	size_t i = 0;
	
	FindTwoMissingNums(arr, 4, result_arr);
	FindTwoMissingNumsByXor(arr ,4);
	for (; i<2; ++i)
	{
		printf("%d\n", result_arr[i]);
	}
	return (0);
}

void FindTwoMissingNums(unsigned int *arr, size_t size, unsigned int *res_arr)
{
	unsigned int arr_sum = 0;
	unsigned int sum_mis_nums;
	unsigned int avg = 0;
	unsigned int sum_below_avg = 0;
	size_t i = 0;
	
	for ( ; i<size; ++i)
	{
		arr_sum += arr[i];
	}
	sum_mis_nums = (((size+2)*(size+2+1)/2) - arr_sum);
	avg = sum_mis_nums/2;
	
	for (i=0 ; i<size; ++i)
	{
		
		if (arr[i] <= avg)
		{
			sum_below_avg += arr[i];
		}
	}
	res_arr[0] = ((avg*(avg+1)/2) - sum_below_avg);
	res_arr[1] = sum_mis_nums - res_arr[0];
}





void FindTwoMissingNumsByXor(unsigned int *arr, size_t size)
{
	int xor = arr[0];
	size_t i = 1;
	size_t series_actual_size = size + 2;
	unsigned int right_set_bit = 0;
	int first_set = 0;
	int second_set = 0;
	
	for ( ; i < size; ++i)
	{
		xor ^= arr[i];	
	}
	
	for (i = 1; i <= series_actual_size; ++i)
	{
		xor ^= i;
	}
	
	/*get the right set bit*/	
	right_set_bit = xor & ~(xor - 1);
	
	for (i = 0 ; i < size; ++i)
	{
		if (arr[i] & right_set_bit)
		{
			first_set = first_set ^ arr[i];
		}
		else
		{
			second_set = second_set ^ arr[i];
		}
	}
	
	for (i = 1; i <= series_actual_size; ++i)
	{
		if (i & right_set_bit)
		{
			first_set = first_set ^ i;
		}
		else
		{
			second_set = second_set ^ i;
		}
	}
	
    printf("In the Xor Function first missing num is: %d\n", first_set);
    printf("In the Xor Function second missing num is: %d\n", second_set);
	

}
