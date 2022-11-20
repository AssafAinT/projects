#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include <limits.h> /* CHAR_BIT */
#include "Ilrd_OL127_128_BitArray.h"


#define NUM_OF_BITS_IN_BIT_ARR (sizeof(bit_array_ty) * CHAR_BIT)


bit_array_ty BitArraySetAll(bit_array_ty bit_arr)
{
	return(bit_arr |= 0xffffffffffffffff);
}


bit_array_ty BitArrayResetAll(bit_array_ty bit_arr)
{
	return(bit_arr &= 0x0);
}


bit_array_ty BitArraySetOn(bit_array_ty bit_arr, size_t index)
{
	size_t mask = 1;
	
	assert(index <= (NUM_OF_BITS_IN_BIT_ARR -1));
	
	mask <<= (index -1);
	
	return (bit_arr |= mask);
}


bit_array_ty BitArraySetOff(bit_array_ty bit_arr, size_t index)
{
	size_t mask = 1;
	
	assert(index <= (NUM_OF_BITS_IN_BIT_ARR -1));
	
	mask <<= (index -1);
	
	return (bit_arr &= (~mask));
}


int BitArrayGetValue(bit_array_ty bit_arr, size_t index)
{
	
	assert(index <= (NUM_OF_BITS_IN_BIT_ARR -1));
	
	return ((bit_arr>>(index-1)) & 1);
}


bit_array_ty BitArraySetBit(bit_array_ty bit_arr, size_t index, size_t bit_value)
{
	size_t mask = 1;
	
	assert(index <= (NUM_OF_BITS_IN_BIT_ARR -1));
	
	mask <<= (index -1);
	
	return ((bit_arr &= (~mask)) | (bit_value << (index - 1)));
}


bit_array_ty BitArrayFlip(bit_array_ty bit_arr)
{
	return(~bit_arr);
}



bit_array_ty BitArrayMirror(bit_array_ty bit_arr)
{
	bit_arr = ((bit_arr & 0x5555555555555555) << 1) |
	 		  ((bit_arr & 0xAAAAAAAAAAAAAAAA) >> 1);
	 
    bit_arr = ((bit_arr & 0x3333333333333333) << 2) |
              ((bit_arr & 0xCCCCCCCCCCCCCCCC) >> 2);
              
    bit_arr = ((bit_arr & 0x0F0F0F0F0F0F0F0F) << 4) |
    		  ((bit_arr & 0xF0F0F0F0F0F0F0F0) >> 4);
    		  
    bit_arr = ((bit_arr & 0x00FF00FF00FF00FF) << 8) |
    		  ((bit_arr & 0xFF00FF00FF00FF00) >> 8);
    		  
    bit_arr = ((bit_arr & 0x0000FFFF0000FFFF) << 16) |
    		  ((bit_arr & 0xFFFF0000FFFF0000) >> 16);
    		  
    bit_arr = ((bit_arr & 0xFFFFFFFFFFFFFFFF) << 32) |
              ((bit_arr & 0xFFFFFFFFFFFFFFFF) >> 32);
              
    
    return(bit_arr);

}



size_t BitArrayCountOn(bit_array_ty bit_arr)
{
	size_t counter = 0;
	
	while(bit_arr)
	{
		counter += (bit_arr & 1);      /* checks if the RMB is on */
		bit_arr >>= 1;
	}
	return counter;
}

size_t BitArrayCountOff(bit_array_ty bit_arr)
{

	return (NUM_OF_BITS_IN_BIT_ARR - BitArrayCountOn(bit_arr));
}


bit_array_ty BitArrayRotateLeft(bit_array_ty bit_arr, size_t rotation_amount)
{
	return((bit_arr << rotation_amount) |
	 	  (bit_arr >> (NUM_OF_BITS_IN_BIT_ARR -rotation_amount)));
}


bit_array_ty BitArrayRotateRight(bit_array_ty bit_arr, size_t rotation_amount)
{
	return((bit_arr >> rotation_amount) |
	      (bit_arr << (NUM_OF_BITS_IN_BIT_ARR -rotation_amount)));
}



char *BitArrayToString(bit_array_ty bit_arr, char *dest)
{
	char *copy_dest = dest;
	size_t i = 0;

	
	assert (NULL != dest);
	
	while(NUM_OF_BITS_IN_BIT_ARR -1 > i)
	{
		*dest = (BitArrayGetValue(bit_arr, NUM_OF_BITS_IN_BIT_ARR-1)) + '0';
		++dest;
		bit_arr <<= 1;
		++i;
	}
	dest = '\0';
	
	return (copy_dest);
}






