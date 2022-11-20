#include <stdio.h>
void PrintNumOfZeros(char ch);
size_t CountSetBitsLongNum(long num);

int main(void)
{
	char test_arr[10] = {1,0,0,1,1,1,0,1,1,1};
	size_t arr_size = 10;
	size_t i = 0;
	long num = 165;
	
	for (; i < arr_size; ++i)
	{
		PrintNumOfZeros(test_arr[i]);
	}
	printf("%ld set bits\n",CountSetBitsLongNum(num));
	return (0);
}

void PrintNumOfZeros(char ch)
{
	static size_t zeros_counter = 0;
	if (0 == ch)
	{
		++zeros_counter;
		printf("till now we encountered %ld zeros\n", zeros_counter);
	}
}

size_t CountSetBitsLongNum(long num)
{
	size_t counter = 0;
	
	for( ; 0 != num; ++counter,printf("i visited here\n"),num &= (num-1));
	
	return (counter);
}

