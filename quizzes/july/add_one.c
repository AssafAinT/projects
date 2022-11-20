#include <stdio.h>
#include <assert.h>
#define CHAR_MAX 255
unsigned char AddOneBitWise(unsigned char num);
unsigned char AddOneBitWiseRecur(unsigned char num);
unsigned char AddOneBitWiseTrick(unsigned char num);
int main(void)
{
	assert(10 == AddOneBitWise(9));
	assert(1 == AddOneBitWise(0));
	
	assert(10 == AddOneBitWiseRecur(9));
	
	assert(10 == AddOneBitWiseTrick(9));
	assert(1 == AddOneBitWiseTrick(0));
	assert(234 == AddOneBitWiseTrick(233));
	
	return (0);
}
unsigned char AddOneBitWise(unsigned char num)
{
	unsigned char mask = 1;
	assert (num < CHAR_MAX);
	
	for ( ; 0 != (num & mask); mask <<= 1)
	{
		num ^= mask;
		
	}
	num ^= mask;
	return (num);
}

unsigned char AddOneBitWiseRecur(unsigned char num)
{
	if (1 != (num & 1))
	{
		return(num ^ 1);
	}
	num = AddOneBitWiseRecur(num >> 1);
	
	return (num << 1);
}

unsigned char AddOneBitWiseTrick(unsigned char num)
{
	assert (num < CHAR_MAX);
	return (-(~num));
}
