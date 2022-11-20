/* WS6 Bitwise 
* Reviewer: Omer Lugassi
* Written by: Assaf Ainhoren Tesler
* Date: 24/05/22
* ***************/



#include <stdio.h>  /* printf */
#include <stddef.h> /*sizeof & size_t */ 
#include <assert.h> /* assert */

#define IS_BIT_ON(byte, i)((byte >> (i-1)) & 1)
#define ARR_SIZE 5
#define CHAR_BITS 8


/*test function */
int RunTests();

/* the function return the result of x*(2^y) */ 
long Pow2(unsigned x, unsigned y);
/* the function checks if a number is a power of 2*/
int IsPow2UsingLoop(unsigned int num);
int IsPow2NoLoop(unsigned int num);

/* the function add 1 to an int without arithmetic operator */
unsigned int AddOne(unsigned int num);

/* the function checks through array the numbers that only have 3 bits on */
void IsThreeBitsOn(unsigned int *arr1, size_t size); 
/* Byte mirror a unsigned char numbers */
unsigned char ByteMirror(unsigned char num);
unsigned char ByteMirrorNoLoop(unsigned char x);

/* the functions check if the 2nd and 6th bits are both set */
int Is2And6BitsOn(unsigned char ch_to_check);
/* the functions check if the 2nd or 6th bits set */
int Is2Or6BitOn(unsigned char ch_to_check);

/* the function swaps between the 3rd and 5th bit */
unsigned char SwapBetweenBits(unsigned char to_swap);
/* checks if the number is divisble by 16 */
unsigned int IsDivisibleBy16(unsigned int num);
/* counts the set bits in a number with/out loop */
unsigned int CountSetBitsUsingLoop(int to_count_bits);
unsigned int CountSetBits(unsigned int num);

/* swap between two variable using bitwise only */
void SwapTwoVarBitWise(unsigned int *x, unsigned int *y);
/* representing Float in binary */
void FloatAnalysis(float num);


int main()
{
	RunTests();
	
	return (0);
}

long Pow2(unsigned int x, unsigned int y)
{
	assert(y <= 31);
	return (x << y);
}

int IsPow2UsingLoop(unsigned int number)
{
	int counter = 0;
	unsigned int copy_number = number;
	

	assert( 0 != number);
	
	while (1 != number)
	{
		number >>= 1;
		++counter;            
	}
    return (copy_number == (number << counter));
}


/* is pow of 2 with bitwise */
int IsPowOf2NoLoop(unsigned int num)
{
	return ((num & (num -1)) == 0);
}



unsigned int AddOne(unsigned int num)
{
	int mask = 1;	
	while( 0 != (num & mask))
	{
		num ^= mask;
		mask <<= 1;
	}
	num ^= mask;
	return num;
	
}
	
void IsThreeBitsOn(unsigned int *arr1, size_t size)
{
	size_t i = 0;
	int count = 0;
	unsigned int copy_of_number = 0;
	
	for( i = 0; i < size ; ++i)
	{
		count = 0 ;
		copy_of_number = arr1[i];
		
		while(arr1[i] > 0)
		{
			if(arr1[i] & 1)
			{
				++count;
			}
			arr1[i] >>= 1;
		}
		if (3 == count)
		{
			printf("%u\n", copy_of_number);
		}
	}
}
	
	
unsigned char ByteMirror(unsigned char num)
{
	unsigned char mirror = 0; 
	unsigned char counter = CHAR_BITS - 1;
	
	while(counter)
	{
		if ((1 & num))
		{
			mirror=AddOne(mirror);
			mirror <<= 1;          /* for making space for the add 1 */
		}
		else
		{
			mirror <<= 1;
		}
		num >>= 1;
		--counter;
	}
	return mirror;
}

unsigned char ByteMirrorNoLoop(unsigned char x) 
{

    x = (((x & 0xaa) >> 1) | ((x & 0x55) << 1));
    x = (((x & 0xcc) >> 2) | ((x & 0x33) << 2));
    x = (((x & 0xf0) >> 4) | ((x & 0x0f) << 4));

    return(x);
}


int Is2And6BitsOn(unsigned char ch_to_check)
{
	return((IS_BIT_ON(ch_to_check, 2)) && (IS_BIT_ON(ch_to_check, 6)));
}


int Is2Or6BitOn(unsigned char ch_to_check)    
{
	return((IS_BIT_ON(ch_to_check, 2)) || (IS_BIT_ON(ch_to_check, 6))); 
}

unsigned char SwapBetweenBits(unsigned char to_swap)
{
	unsigned char result = 0;
	unsigned char bit3 = 0;
	unsigned char bit5 = 0;
	unsigned char temp_store = 0;
	
	bit3 = ((to_swap & 4) == 4);
	bit5 = ((to_swap & 16) == 16);
	temp_store = bit3 ^ bit5;
	temp_store = (temp_store << 2) | (temp_store << 4);
	result = to_swap ^ temp_store;
	
	return result;
} 

unsigned int IsDivisibleBy16(unsigned int num)
{
	return ((num &0xfffffff0));         
} 

void SwapTwoVarBitWise(unsigned int *x, unsigned int *y)
{
	*x ^= *y;
	*y ^= *x;
	*x ^= *y;
}

unsigned int CountSetBitsUsingLoop(int to_count_bits)
{
	int counter = 0;
	
	while(to_count_bits)
	{
		counter += (to_count_bits & 1);      /* checks if the RMB is on */
		to_count_bits >>= 1;
	}
	return counter;
}

unsigned int CountSetBits(unsigned int num)
{
	num -= ((num >> 1) & 0x5555555555);
	num = ( num & 0x33333333) + ((num >> 2) & 0x33333333);
	num = ( num + ( num >> 4)) & 0x0F0F0F0F;
	num += ( num >> 8 );
	num += ( num >> 16 );
	
	return (num & 0x0000003F);
}

void FloatAnalysis(float num)
{
	
	int *i = (int *)&num;
	int index = 31;
	
	while (index)
	{
		printf("%d",(*i >> index) & 1);
		--index;
	}
	printf("\n");
}


	
int RunTests()
{
	unsigned int x = 3;
	unsigned int y = 0; 
	unsigned int n = 32;
	unsigned int n_to_add = 257;
	unsigned int arr_to_send[5] = {7, 14, 25, 4, 32};
	unsigned int what_remains = 1234567;
	unsigned char mirror_num = 1;
	unsigned char to_bits_on = 190;
	unsigned char to_one_bit_on = 11;
	unsigned char need_to_swap = 255;
	unsigned int how_many_bits_on = 71;
	float num_to_print_bin = 3.14;
	
	unsigned int swap1 = 7;
	unsigned int swap2 = 6;
	
	Pow2(x , y);
	printf("%d returns from IsPow2UsingLoop\n", IsPow2UsingLoop(n));
	printf("%d returns from IsPow2NoLoop\n", IsPowOf2NoLoop(n)); 
	printf("%d returns from AddOne\n", AddOne(n_to_add));
	IsThreeBitsOn(arr_to_send, ARR_SIZE);
	printf("%u returns from ByteMirror\n", ByteMirror(mirror_num));
	printf("%u returns from ByteMirrorNoLoop\n", ByteMirrorNoLoop(mirror_num));
	printf("%d returns from Is2And6BitsOn Function\n", Is2And6BitsOn(to_bits_on));
	printf("%d returns from Is2Or6BitOne Function\n", Is2Or6BitOn(to_one_bit_on));
	printf("%d returns from CountSetBitsUsingLoop\n", 	CountSetBitsUsingLoop(how_many_bits_on));
	printf("%d returns from CountSetBits\n", CountSetBits(how_many_bits_on));
	printf("%u returns from IsDivisibleBy16\n", IsDivisibleBy16(what_remains));
	printf("%d returns from SwapBetweenBits\n", SwapBetweenBits(need_to_swap));
	SwapTwoVarBitWise(&swap1, &swap2);
	printf("after SwapTwoVarBitWise the numbers now %d %d\n", swap1, swap2);
	FloatAnalysis(num_to_print_bin);
	
	return (0);
}

