#include <stdio.h> /*for print and test */
#include <limits.h> /* CHAR_BIT */
#include "bit_array.h"

#define NUM_OF_BITS_IN_BIT_ARR (sizeof(bit_array_ty) * CHAR_BIT)

int main(void)
{
	bit_array_ty bit_arr = 0xaa;
	bit_array_ty bit_arr_to_set = 0xcab;
	char bits_represent[NUM_OF_BITS_IN_BIT_ARR] = "";
	
	
	BitArrayToString(BitArraySetAll(bit_arr), bits_represent);
	puts(bits_represent);
	
	BitArrayToString(BitArrayResetAll(bit_arr), bits_represent);
	puts(bits_represent);
	
	BitArrayToString(BitArraySetOn(0x0000000000000000, 3), bits_represent);
	puts(bits_represent);
	
	BitArrayToString(BitArraySetOff(0xffffffffffffffff, 2), bits_represent);
	puts(bits_represent);
	
	printf("%d\n",BitArrayGetValue(bit_arr_to_set,12));
	
	BitArrayToString(BitArraySetBit(bit_arr_to_set,3,3), bits_represent);
	puts(bits_represent);
	
	printf("before mirror %s\n and after: ",BitArrayToString(bit_arr_to_set, bits_represent));
	BitArrayToString(BitArrayMirror(bit_arr_to_set), bits_represent);
	puts(bits_represent);
	
	BitArrayToString(BitArrayFlip(bit_arr), bits_represent);
	puts(bits_represent);
	
	
	printf("%ld bits on\n", BitArrayCountOn(bit_arr_to_set));
	printf("%ld bits off\n", BitArrayCountOff(bit_arr));

	BitArrayToString(BitArrayRotateLeft(bit_arr, 6), bits_represent);
	puts(bits_represent);
	
	BitArrayToString(BitArrayRotateRight(bit_arr, 8), bits_represent);
	puts(bits_represent);
	
	
	BitArrayToString(bit_arr, bits_represent);
	puts(bits_represent);
	
	
	printf("BitArraySetOn: \t\t%s\n",
            BitArrayToString(BitArraySetOn(0x0000000000000000, 3), bits_represent));

    printf("BitArraySetOff: \t%s\n",
            BitArrayToString(BitArraySetOff(0xffffffffffffffff, 3), bits_represent));
	
	return (0);
}
