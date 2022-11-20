/*****************************************************
 * WS11                                              *
 * Assaf Ainhoren                                    *
 * Reviewer: Ofir Krisple                            *
 * date: 05.06.2022                                  *
 *****************************************************/
 
/********************************libraries includes****************************/
 
#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include <limits.h> /* CHAR_BIT */
#include "bit_array.h"

/********************************Macros includes*******************************/

/*define for the mirror function using LUT*/
#define MIR2(n) n, n + 2*64, n + 1*64, n + 3*64
#define MIR4(n) MIR2(n), MIR2(n + 2*16), MIR2(n + 1*16), MIR2(n + 3*16)
#define MIR6(n) MIR4(n), MIR4(n + 2*4 ), MIR4(n + 1*4 ), MIR4(n + 3*4 )
#define MIRROR_BITS MIR6(0), MIR6(2), MIR6(1), MIR6(3)

/*define for the count function using LUT*/
#define C2(n)     n,     n + 1,     n + 1,     n + 2
#define C4(n) C2(n), C2(n + 1), C2(n + 1), C2(n + 2)
#define C6(n) C4(n), C4(n +1), C4(n + 1 ), C4(n + 2 )
#define COUNT_BITS C6(0), C6(1), C6(1), C6(2)


#define NUM_OF_BITS_IN_BIT_ARR (sizeof(bit_array_ty) * CHAR_BIT)
#define MAX_NUM_BIT_ARRAY_TY 0xffffffffffffffff

/**************************Creating LUT For Mirror and Count Functions*********/
static const bit_array_ty BitMirrorTable[256] = { MIRROR_BITS };
static const bit_array_ty BitCountTable[256] = {COUNT_BITS};

/*********************************Functions Definitions************************/
bit_array_ty BitArraySetAll(bit_array_ty bit_arr)
{
	assert(bit_arr <= MAX_NUM_BIT_ARRAY_TY);
	
	return (bit_arr |= MAX_NUM_BIT_ARRAY_TY);
}


bit_array_ty BitArrayResetAll(bit_array_ty bit_arr)
{
	assert(bit_arr <= MAX_NUM_BIT_ARRAY_TY);
	
	return (bit_arr &= 0x0);
}



bit_array_ty BitArraySetOn(bit_array_ty bit_arr, size_t index)
{
	size_t mask = 1;
	assert(bit_arr <= MAX_NUM_BIT_ARRAY_TY);
	assert(index <= (NUM_OF_BITS_IN_BIT_ARR));
	
	mask <<= (index);
	
	return (bit_arr | mask);
}


bit_array_ty BitArraySetOff(bit_array_ty bit_arr, size_t index)
{
	size_t mask = 1;

	assert(bit_arr <= MAX_NUM_BIT_ARRAY_TY);
	assert(index <= (NUM_OF_BITS_IN_BIT_ARR));
	
	mask <<= (index);
	
	return (bit_arr &= (~mask));
} 

int BitArrayGetValue(bit_array_ty bit_arr, size_t index)
{
	assert(bit_arr <= MAX_NUM_BIT_ARRAY_TY);
	assert(index <= (NUM_OF_BITS_IN_BIT_ARR));
	
	return ((bit_arr >> index) & (bit_array_ty)1);
}


bit_array_ty BitArraySetBit(bit_array_ty bit_arr, size_t index, size_t bit_value)
{
	size_t mask = 1;
	
	assert(index <= (NUM_OF_BITS_IN_BIT_ARR));
	bit_value = (!(!(bit_value))); /* turn input into boolian , and flip value */
	bit_arr = BitArraySetOff(bit_arr, index);
	return (bit_arr | (bit_value << index));

}


bit_array_ty BitArrayFlip(bit_array_ty bit_arr)
{
	assert(bit_arr <= MAX_NUM_BIT_ARRAY_TY);
	
	return (~bit_arr);
}



bit_array_ty BitArrayMirror(bit_array_ty bit_arr)
{
	/************divide and conqure method **********
		
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
    		  
    bit_arr = ((bit_arr & MAX_NUM_BIT_ARRAY_TY) << 32) |
              ((bit_arr & MAX_NUM_BIT_ARRAY_TY) >> 32);
     *************************************************/
	assert(bit_arr <= MAX_NUM_BIT_ARRAY_TY);              					  
    
    return(BitMirrorTable[bit_arr & 0xff] << 56) |
 		 (BitMirrorTable[(bit_arr >> 8) & 0xff] << 48) |
  		 (BitMirrorTable[(bit_arr >> 16) & 0xff] << 40) |
         (BitMirrorTable[(bit_arr >> 24) & 0xff] << 32) | 
         (BitMirrorTable[(bit_arr >> 32) & 0xff] << 24) |
         (BitMirrorTable[(bit_arr >> 40) & 0xff] << 16) |
         (BitMirrorTable[(bit_arr >> 48) & 0xff] << 8) |
         (BitMirrorTable[(bit_arr >> 56) & 0xff] );


}



size_t BitArrayCountOn(bit_array_ty bit_arr)
{
	/* size_t counter = 0; */
	
	/*while (bit_arr) 
	{
		counter += (bit_arr & 1);
		bit_arr >>= 1;
	}*/
	assert(bit_arr <= MAX_NUM_BIT_ARRAY_TY);
	
	return (BitCountTable[bit_arr & 0xff]) +
 		 (BitCountTable[(bit_arr >> 8) & 0xff]) +
  		 (BitCountTable[(bit_arr >> 16) & 0xff]) +
         (BitCountTable[(bit_arr >> 24) & 0xff]) + 
         (BitCountTable[(bit_arr >> 32) & 0xff]) +
         (BitCountTable[(bit_arr >> 40) & 0xff]) +
         (BitCountTable[(bit_arr >> 48) & 0xff]) +
         (BitCountTable[(bit_arr >> 56) & 0xff]);

}

size_t BitArrayCountOff(bit_array_ty bit_arr)
{
	assert(bit_arr <= MAX_NUM_BIT_ARRAY_TY);
	
	return (NUM_OF_BITS_IN_BIT_ARR - BitArrayCountOn(bit_arr));
}


bit_array_ty BitArrayRotateLeft(bit_array_ty bit_arr, size_t rotation_amount)
{
	assert(bit_arr <= MAX_NUM_BIT_ARRAY_TY);
	
	return((bit_arr << rotation_amount) |
	 	  (bit_arr >> (NUM_OF_BITS_IN_BIT_ARR -rotation_amount)));
}


bit_array_ty BitArrayRotateRight(bit_array_ty bit_arr, size_t rotation_amount)
{
	assert(bit_arr <= MAX_NUM_BIT_ARRAY_TY);
	
	return((bit_arr >> rotation_amount) |
	      (bit_arr << (NUM_OF_BITS_IN_BIT_ARR -rotation_amount)));
}



char *BitArrayToString(bit_array_ty bit_arr, char *dest)
{
	char *copy_dest = dest;
	size_t i = NUM_OF_BITS_IN_BIT_ARR;

	assert(bit_arr <= MAX_NUM_BIT_ARRAY_TY);	
	assert (NULL != dest);
	
	while (0 < i)
	{
		*dest = (BitArrayGetValue(bit_arr,i)) + '0';
		++dest;
		--i;
	}
	
	*dest = '\0';
	
	return (copy_dest);
}







