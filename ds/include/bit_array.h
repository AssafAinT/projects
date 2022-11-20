#ifndef __ILRD_OL127_128_BITARRAY_H__
#define __ILRD_OL127_128_BITARRAY_H__

#include <stddef.h>


typedef size_t bit_array_ty;

/* the function sets all the bits in the bit_array to on.
 returns the set bit_array. Time-Complexity - O(n) */
bit_array_ty BitArraySetAll(bit_array_ty bit_arr);

/* the function sets all the bits in the bit_array to off.
 returns the set bit_array. Time-Complexity - O(n)
 exceptions: will generate error if the
 out param is bigger than maximum-number of 64 bits. */
bit_array_ty BitArrayResetAll(bit_array_ty bit_arr);

/* the function sets specifed the bits in the bit_array to on.
 returns the set bit_array. Time-Complexity - O(1).
 exceptions: will generate error (1)if the
 first out param is bigger than maximum-number of 64 bits.
 (2) if the index is bigger than 64 bits   */
bit_array_ty BitArraySetOn(bit_array_ty bit_arr, size_t index);

/* the function sets specifed the bits in the bit_array to off.
 returns the set bit_array. Time-Complexity - O(1)
 exceptions: will generate error (1)if the
 first out param is bigger than maximum-number of 64 bits.
 (2) if the index is bigger than 64 bits */
bit_array_ty BitArraySetOff(bit_array_ty bit_arr, size_t index);

/* the function gets bit status in specified index from the bit_array.
 returns 1 if on or 0 if off. Time-Complexity - O(1).
 exceptions: will generate error (1)if the
 first out param is bigger than maximum-number of 64 bits.
 (2) if the index is bigger than 64 bits */
int BitArrayGetValue(bit_array_ty bit_arr, size_t index);

/* the function sets a specified bit in the bit_array.
 in this functions the bit value that is send is converted to boolean.
 returns a copy of the bitarray with the set bit. Time-Complexity - O(n)
 exceptions: will generate error (1)if the
 first out param is bigger than maximum-number of 64 bits.
 (2) if the index is bigger than 64 bits */
bit_array_ty BitArraySetBit(bit_array_ty bit_arr, size_t index, size_t bit_value);

/* the function flips the bit status in the bit_array.
 returns 1 if on or 0 if off. Time-Complexity - O(n).
 exceptions: will generate error if the
 out param is bigger than maximum-number of 64 bits. */
bit_array_ty BitArrayFlip(bit_array_ty bit_arr);

/*Mirrors the bits in BitArray. returns mirrored copy of the bitarray using LUT.
 time-complexity O(1).
 exceptions: will generate error if the
 out param is bigger than maximum-number of 64 bits. */

bit_array_ty BitArrayMirror(bit_array_ty bit_arr);

/* the function count set bits status in the bit_array using LUT.
 returns the amount of set bits. Time-Complexity - O(1)
 exceptions: will generate error if the
 out param is bigger than maximum-number of 64 bits. */

size_t BitArrayCountOn(bit_array_ty bit_arr);

/* the function count the un-set bits status in the bit_array using LUT.
 returns the amount of off bits. Time-Complexity - O(1).
 exceptions: will generate error if the
 out param is bigger than maximum-number of 64 bits. */

size_t BitArrayCountOff(bit_array_ty bit_arr);

/* the function rotates the bit_array to the left.
 returns a copy of the bitarray. Time-Complexity - O(1)
 exceptions: will generate error (1)if the
 first out param is bigger than maximum-number of 64 bits.
 (2) if the index is bigger than 64 bits */
bit_array_ty BitArrayRotateLeft(bit_array_ty bit_arr, size_t rotation_amount);

/* the function rotates the bit_array to the right.
 returns a copy of the bitarray. Time-Complexity - O(1).
 exceptions: will generate error if the
 out param is bigger than maximum-number of 64 bits. */
bit_array_ty BitArrayRotateRight(bit_array_ty bit_arr, size_t rotation_amount);

/* the function makes a string representing the value of the bitarray.
 returns a pointer to the destination buffer. Time-Complexity - O(n).
 exceptions: will generate error (1)if the
 first out param is bigger than maximum-number of 64 bits.
 (2) if the dest buffer in not-valid(NULL)*/
char * BitArrayToString(bit_array_ty bit_arr, char *dest);


#endif /* __ILRD_OL127_128_BITARRAY_H__ */
