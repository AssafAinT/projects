/*****************************************************
 * Circular Buffer                                   *
 * Assaf Ainhoren                                    *
 * Reviewer:                                         *
 * date:                                             *
 *****************************************************/
#ifndef __ILRD_OL_127_128_CIR_BUFF_H__
#define __ILRD_OL_127_128_CIR_BUFF_H__

/***************************************libraries include**********************/
#include <stddef.h>  /* size_t */
#include <unistd.h> /* ssize_t */


typedef struct circular_buff cbuff_ty;

/* Description: Creating Circular_buff. 
Return value: a pointer to the new created list.
			upon failure : NULL.
Complexity:
Time - O(1).
Space -O(n).*/
cbuff_ty *CBuffCreate(size_t capacity);

/* Description: Destroy Circular_buff.
Complexity:
Time - O(n).
Space -O(1).*/
void CBuffDestroy(cbuff_ty *cbuff);

/* Description: Writing n bytes of data to the buffer provided by a src.
Return value: On  success,  the  number of bytes written is returned.
On error, -1 is returned
Complexity:
Time - O(n).
Space -O(1).*/
ssize_t CBuffWrite(cbuff_ty *cbuff, const char *src, size_t count);

/* Description: Reading n bytes of data from the buffer to a dest.
Return value: On  success,  the  number of bytes written is returned.
0 indicates EOF.
Complexity:
Time - O(n).
Space -O(1).*/
ssize_t CBuffRead(cbuff_ty *cbuff, char *dest, size_t count);

/* Description: Returning the capacity of the Circular buffer.
	Sending an invalid pointer would result an undefined behavior.
Complexity:
Time - O(1).
Space -O(1).*/
size_t CBuffCapacity(const cbuff_ty *cbuff);

/* Description: Returning the amount of free space available to write.
	Sending an invalid pointer would result an undefined behavior.
Complexity:
Time - O(1).
Space -O(1).*/
size_t CBuffFreeSpace(const cbuff_ty *cbuff);
/* Description: Computing for the emptiness of the circular buffer.
	Return Value: If empty returns 1, otherwise 0.
	Sending an invalid pointer would result an undefined behavior.
Complexity:
Time - O(1).
Space -O(1).*/
int CBuffIsEmpty(const cbuff_ty *cbuff);

#endif /* __ILRD_OL_127_128_CIR_BUFF_H__ */
