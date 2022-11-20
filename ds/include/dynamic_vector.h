#ifndef __ILRD_OL127_128_VECTOR_H__ /* header-guard */
#define __ILRD_OL127_128_VECTOR_H__


#include <stddef.h> /* size_t */
#include "utils.h"
typedef struct vector vector_ty;

/* Creates the vector. returnes a pointer to the beginning of the vector.
 time-complexity-O(n) */
vector_ty *VectorCreate(size_t element_amount, size_t element_size);

/* Frees the vector.
 time-complexity-O(1) */
void VectorDestroy(vector_ty *vector);

/* The function returns the user the current size of the vector. 
 Time-Complexity - O(1) */
size_t VectorSize(const vector_ty *vector);

/* The function returns the user the Maximum capacity of the vector(in bytes)
Time-Complexity O(1) */
size_t VectorCapacity(const vector_ty *vector);

/* Changes the size of the vector. returnes exit_status. time-complexity-O(n) */
status_ty VectorResize(vector_ty *vector, size_t new_element_amount);

/* The function insert a data to the vector.
 Time complexity O(1)*/ 
status_ty VectorPushBack(vector_ty *vector, const void *data);

/* The function pop to the data out of the vector.
 Time complexity O(1)*/
void VectorPopBack(vector_ty *vector);

/* the function returns the a pointer to data in specified element sent by user.
 time complexity O(1) */
void *VectorGetElement(const vector_ty *vector, size_t index);

/* the function checks if the vector is empty.
return either SUCCESS or Fail 
Time Complexity O(1) */
status_ty VectorIsEmpty(const vector_ty *vector);

/* Advanced */
void VectorSetElement(vector_ty *vector, size_t index, void *data);

#endif /* __ILRD_OL127_128_VECTOR_H__ */
