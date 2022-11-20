#include <stdio.h>

int CountCouplesSetBits(unsigned char num);
void SwapTwoInts(unsigned int *a, unsigned int *b);
unsigned int CountSetBitsLoop(unsigned long  int number);

int main()
{
	unsigned char num_to_count_bits = 211;
	unsigned int num1 = 5;
	unsigned int num2 = 23;
	unsigned long int num_to_count = 125;
	SwapTwoInts(&num1, &num2);
	printf("\n%d of set bits\n", CountSetBitsLoop(num_to_count));	
	printf("after the swap the numbers are %d %d\n", num1, num2);
	printf("\n%d couple of set bits\n", CountCouplesSetBits(num_to_count_bits));
		
	return (0);
}

int CountCouplesSetBits(unsigned char num)
{
	size_t set_bits = 0;
	
	while(0 < num)
	{
		if((num & 1) && ((num >> 1) & 1))
		{
			++set_bits;
		}
		num >>= 1;
	}
	
	return set_bits;

}

void SwapTwoInts(unsigned int *a, unsigned int *b)
{
	unsigned int copy_number = *a;
	
	/* method no1
	 *a ^= *b;
	*b ^= *a;
	*a ^= *b; */
	
	/*method no2
	 *a += *b;
	*b -= *a;
	*a -= *b; */
	
	/* method no 3 */
	
	*a = *b;
	*b = copy_number;
}



unsigned int CountSetBitsLoop(unsigned long int number)
{
	size_t set_bit_counter = 0;
	
	while(number)
	{
		number &= (number-1);
		++set_bit_counter;
	}
	return set_bit_counter;
}

