/*****************************************************
 * Vector WS                                         *
 * Assaf Ainhoren                                    *
 * Reviewer: Noa Dudai                               *
 * date: 05.06.2022                                  *
 *****************************************************/


/********************************libraries includes****************************/
#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include <string.h> /*memcpy */

#include "dynamic_vector.h" /* header */

/********************************vector definition*****************************/
struct vector 
{
	char *vector;
	size_t capacity;
	size_t size_of_element;
	size_t current_size;
};

/********************************Macros definition*****************************/
#define GROWTH_FACTOR 2

/********************************Functions definition**************************/
vector_ty *VectorCreate(size_t element_amount, size_t element_size)
{
	vector_ty *new_vector = (vector_ty *)malloc(sizeof(vector_ty));
	
	if (NULL == new_vector)
	{
		return (NULL);
	}
	
	new_vector->capacity = element_amount * element_size;
	new_vector->size_of_element = element_size;
	
	new_vector->vector = (char *)malloc(new_vector->capacity);
  	
	
	if (NULL == new_vector->vector)
	{
		free(new_vector);
		return (NULL);
	}
	
  	new_vector->current_size = 0;

	return (new_vector);
}

void VectorDestroy(vector_ty *vector)
{
	assert(NULL != vector);
	assert(NULL != vector->vector);
	
	free (vector->vector);
	free (vector);
	
}

size_t VectorSize(const vector_ty *vector)
{
	assert(NULL != vector);
	assert(NULL != vector->vector);
	
	return (vector->current_size);
}

size_t VectorCapacity(const vector_ty *vector)
{
	assert(NULL != vector);
	assert(NULL != vector->vector);
	
	return (vector->capacity);
		
}

status_ty VectorResize(vector_ty *vector, size_t new_element_amount)
{
	char *vector_copy = NULL;
	
	assert(NULL != vector);
	assert(NULL != vector->vector);
	
	vector_copy = realloc(vector->vector, (new_element_amount * 
					      vector->size_of_element));
					      
	if (NULL == vector_copy)
	{
		return FAIL;
	}
	
	vector->vector = vector_copy;
	vector->capacity = new_element_amount * vector->size_of_element;
	
	return SUCCESS;
} 

status_ty VectorPushBack(vector_ty *vector, const void *data)
{
	size_t index = 0;
	
	assert(NULL != vector);
	assert(NULL != vector->vector);
	
	if (vector->current_size == (vector->capacity/vector->size_of_element))
	{
		if (FAIL==VectorResize(vector, GROWTH_FACTOR *
							 (vector->capacity / vector->size_of_element)))
		{
			return FAIL;
		}
	}
	
	index = (vector -> current_size) * (vector -> size_of_element);
	memcpy((vector->vector + index), data, vector->size_of_element);
	
	
	
	vector->current_size += 1;
	
	return SUCCESS;
}

void VectorPopBack(vector_ty *vector)
{
	assert(NULL != vector);
	assert(NULL != vector->vector);
	
	vector->current_size -= 1;
	
	
}

void *VectorGetElement(const vector_ty *vector, size_t index)
{
	void *element = NULL;
	
	assert(NULL != vector);
	assert(NULL != vector->vector);
	
	element = (vector -> vector) + (index  * (vector -> size_of_element));
	
	return element;
}

status_ty VectorIsEmpty(const vector_ty *vector)
{
	assert(NULL != vector);
	assert(NULL != vector->vector);
	
	return((vector -> current_size) == 0 ? SUCCESS : FAIL);
}

void VectorSetElement(vector_ty *vector, size_t index, void *data)
{
    assert(NULL != vector);
    assert(NULL != data);

    memcpy(vector->vector + (vector->size_of_element* index),
    data, vector->size_of_element);
}