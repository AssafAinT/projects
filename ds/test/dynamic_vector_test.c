#include <stdio.h> /*printf */
#include <assert.h> /* assert */

#include "dynamic_vector.h" /* header */

int main()
{
	int first_data = 12;
	int sec_data = 13;
	int third_data = 5;
	
	vector_ty *vector_first = VectorCreate(8, 4);
	
	assert(32 == VectorCapacity(vector_first));
	assert(0 == VectorSize(vector_first));
	
	VectorPushBack(vector_first, &first_data);
	VectorPushBack(vector_first, &sec_data);
	
	printf("%d\n", *(int *)VectorGetElement(vector_first, 0));
	printf("%d\n", *(int *)VectorGetElement(vector_first, 1));
	
	assert(2 == VectorSize(vector_first));
	assert(32 == VectorCapacity(vector_first));
	
	VectorResize(vector_first, 5); 
	
	assert(2 == VectorSize(vector_first));
	assert(20 == VectorCapacity(vector_first));
	
		
	VectorPushBack(vector_first, &third_data);
	VectorPushBack(vector_first, &first_data);
	
	VectorPopBack(vector_first);
	assert(3 == VectorSize(vector_first));
	
	printf("%d\n", *(int *)VectorGetElement(vector_first, 2));
	
	VectorResize(vector_first, 23);
	assert(3 == VectorSize(vector_first));
	assert(92 == VectorCapacity(vector_first));
	
	VectorResize(vector_first, 3);
	assert(3 == VectorSize(vector_first));
	assert(12 == VectorCapacity(vector_first));	
	
	if (FAIL ==VectorIsEmpty(vector_first))
	{
		printf("vector is not empty\n");
	}	
	else
	{
		printf("vector is empty\n");
	}
	
	VectorPopBack(vector_first);
	if (FAIL ==VectorIsEmpty(vector_first))
	{
		printf("vector is not empty\n");
	}	
	else
	{
		printf("vector is empty\n");
	}
	
	VectorPopBack(vector_first);
	if (FAIL ==VectorIsEmpty(vector_first))
	{
		printf("vector is not empty\n");
	}	
	else
	{
		printf("vector is empty\n");
	}
	VectorPopBack(vector_first);
	if (FAIL ==VectorIsEmpty(vector_first))
	{
		printf("vector is not empty\n");
	}	
	else
	{
		printf("vector is empty\n");
	}
	VectorDestroy(vector_first);
	
	return (0);
}

