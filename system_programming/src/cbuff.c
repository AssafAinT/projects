/*****************************************************
 * Circular Buffer                                   *
 * Assaf Ainhoren                                    *
 * Reviewer:                                         *
 * date:                                             *
 *****************************************************/

/********************************libraries includes****************************/
#include <stddef.h> /*size_t */
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */
#include <string.h> /* memcpy */

#include "cbuff.h"
/********************************struct definition*****************************/
struct circular_buff
{
    size_t read_index;
	size_t current_size;
    size_t capacity;
    char data[1];
};
/********************************struct definition*****************************/
/* Description:
	Returning the actual available size inorder to avoid over-read/write 
Time complexity - O(1)*/
static size_t CountUpdate(cbuff_ty *cbuff, size_t count);
/* Description:
	Writing to from an element in the buffer that during writing we will complete
	a circle of it 
Time complexity - O(n)*/
static void CbuffCirucalryWrite(cbuff_ty *cbuff,const  char *src, size_t count,
size_t index);
/* Description:
	reading to from an element in the buffer that during reading we will complete
	a circle of it 
Time complexity - O(n)*/
static void CbuffCirCularRead(cbuff_ty *cbuff, char *dest, size_t count);

static void CBuffReadForward(cbuff_ty *cbuff, char *dest, size_t count);
/********************************function declarations*************************/

/*----------------------------------------------------------------------------*/
/*                                 CBuffCreate                                */
/*----------------------------------------------------------------------------*/
cbuff_ty *CBuffCreate(size_t capacity)
{
	cbuff_ty *cir_buff = NULL;
	size_t corrected_struct_size = (offsetof(cbuff_ty, data) + capacity);
	 
	cir_buff = (cbuff_ty *)malloc(corrected_struct_size);
	
	if (NULL == cir_buff)
	{
		return (NULL);	
	}
	
	cir_buff->read_index = 0;
	cir_buff->current_size = 0;
	cir_buff->capacity = capacity;
	
	return (cir_buff);
}
/*----------------------------------------------------------------------------*/
/*                                 CBuffDestory                               */
/*----------------------------------------------------------------------------*/
void CBuffDestroy(cbuff_ty *cbuff)
{
	assert(NULL != cbuff);
	
	free(cbuff);
}
/*----------------------------------------------------------------------------*/
/*                                 Write                                      */
/*----------------------------------------------------------------------------*/

ssize_t CBuffWrite(cbuff_ty *cbuff, const char *src, size_t count)
{
	ssize_t write_index = 0;

	if (NULL == cbuff || NULL == src)
	{
		return (-1);
	}

	count = CountUpdate(cbuff, count);
	write_index = ((cbuff->read_index)+(cbuff->current_size)) % (cbuff->capacity);
	
	cbuff->current_size += count;
	/* write forward */
	if (count <= (cbuff->capacity - write_index))
	{
		memcpy(&(cbuff->data[write_index]), src, count); 
	}
	
	else
	{
		CbuffCirucalryWrite(cbuff, src, count, write_index);
	}

	return (count);
}
/*----------------------------------------------------------------------------*/
/*                                 CountUpdate                                */
/*----------------------------------------------------------------------------*/

static size_t CountUpdate(cbuff_ty *cbuff, size_t count)
{
	return (count = (count <= CBuffFreeSpace(cbuff)) ?
		    count : CBuffFreeSpace(cbuff));
}
/*----------------------------------------------------------------------------*/
/*                                 CbuffCirucalryWrite                        */
/*----------------------------------------------------------------------------*/
static void CbuffCirucalryWrite(cbuff_ty *cbuff,const  char *src, size_t count,
size_t index)
{
		size_t byte_to_write =  (cbuff->capacity - index ) % count;
		
		memcpy(&(cbuff->data[index]), src, byte_to_write); 
		src += byte_to_write;
		byte_to_write = count - byte_to_write;
		memcpy(&(cbuff->data[0]), src, byte_to_write);
}
/*----------------------------------------------------------------------------*/
/*                                 Read                                       */
/*----------------------------------------------------------------------------*/
ssize_t CBuffRead(cbuff_ty *cbuff, char *dest, size_t count)
{
	if (NULL == cbuff || NULL == dest)
	{
		return (-1);
	}
	count = (count >= cbuff->current_size) ? cbuff->current_size : count;
	cbuff->current_size -= count;

	
	
	if (count <= (cbuff->capacity - cbuff->read_index))
	{
		CBuffReadForward(cbuff, dest, count);
	}
	else
	{
		CbuffCirCularRead(cbuff, dest, count);	
	}
	
	return (count);
}
/*----------------------------------------------------------------------------*/
/*                                 ForWardRead                                */
/*----------------------------------------------------------------------------*/
static void CBuffReadForward(cbuff_ty *cbuff, char *dest, size_t count)
{
		memcpy(dest, &(cbuff->data[cbuff->read_index]), count);
		cbuff->read_index = (cbuff->read_index + count)% cbuff->capacity ;
}
/*----------------------------------------------------------------------------*/
/*                                 CircularRead                               */
/*----------------------------------------------------------------------------*/
static void CbuffCirCularRead(cbuff_ty *cbuff, char *dest, size_t count)
{
		size_t bytes_to_read = 0; 
		bytes_to_read =  (cbuff->capacity - cbuff->read_index) % count;
		CBuffReadForward(cbuff, dest, bytes_to_read);
		
		dest += bytes_to_read;
		bytes_to_read = count - bytes_to_read;
		memcpy(dest , &(cbuff->data[0]), bytes_to_read);		
}

/*----------------------------------------------------------------------------*/
/*                                 Capacity                                   */
/*----------------------------------------------------------------------------*/
size_t CBuffCapacity(const cbuff_ty *cbuff)
{
	assert(NULL != cbuff);
	
	return (cbuff->capacity);
}
/*----------------------------------------------------------------------------*/
/*                                 FreeSpace                                  */
/*----------------------------------------------------------------------------*/
size_t CBuffFreeSpace(const cbuff_ty *cbuff)
{
	assert(NULL != cbuff);

	return (CBuffCapacity(cbuff) - (cbuff->current_size));
}
/*----------------------------------------------------------------------------*/
/*                              IsEmpty                                       */
/*----------------------------------------------------------------------------*/
int CBuffIsEmpty(const cbuff_ty *cbuff)
{
	assert(NULL != cbuff);
	
	return ((0==cbuff->current_size));
}


