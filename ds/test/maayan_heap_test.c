/*****************************************************
 * Test file of heap.
 * Date : 31.07.2022
 * Author : Maayan Sheraizin
 * Reviewer : Avia
 *****************************************************/

#include <stddef.h> /*size_t, NULL */
#include <stdio.h> /*printf*/
#include "heap.h" 


typedef enum
{
	TEST_SUCCESS	= 0,
	MALLOC_FAIL		= 1,
	ISEMPTY_FAIL	= 2,
	PUSH_FAIL		= 3,
	POP_FAIL 		= 4,
	PEEK_FAIL 		= 5,
	REMOVE_FAIL		= 6,
	SIZE_FAIL		= 7
}test_return_status_ty;




test_return_status_ty TestCreateDestroy(void);
test_return_status_ty TestPushPeek(void);
test_return_status_ty TestPop(void);
test_return_status_ty TestRemove(void);

static int Cmp(const void *heap_data, const void *user_data, void *params);
static bool_ty IsRemoveMatch(const void *heap_data, void *root_data);

int main(void)
{
	test_return_status_ty return_status = TEST_SUCCESS;
	
	return_status = TestCreateDestroy();
 	if (TEST_SUCCESS != return_status)
	{
		return return_status;	
	}
	
	return_status = TestPushPeek();
 	if (TEST_SUCCESS != return_status)
	{
		return return_status;	
	}
	return_status = TestPop();
 	if (TEST_SUCCESS != return_status)
	{
		return return_status;	
	}
	return_status = TestRemove();
 	if (TEST_SUCCESS != return_status)
	{
		return return_status;	
	}
	return TEST_SUCCESS;
}
 
/*
*should be tested with vlg
*/
test_return_status_ty TestCreateDestroy(void)
{
	heap_ty *heap = HeapCreate(Cmp, NULL);
	if (NULL == heap)
	{
		return MALLOC_FAIL;
	}
	if (!HeapIsEmpty(heap))
	{
		HeapDestroy(heap);
		return ISEMPTY_FAIL;
	}
	
	if (0 != HeapSize(heap))
	{
		HeapDestroy(heap);
		return SIZE_FAIL;
	}
	
	HeapDestroy(heap);	
	return TEST_SUCCESS;
}


test_return_status_ty TestPushPeek(void)
{
	int array_1[] = {2,1,3};
	int array_2[] = {15,30,50,100,40,10,20};
	size_t indx = 0; 
	heap_ty *heap_1 = NULL; 
	heap_ty *heap_2 = HeapCreate(Cmp, NULL);
	if (NULL == heap_2)
	{
		return MALLOC_FAIL;
	}
	heap_1 = HeapCreate(Cmp, NULL);
	if (NULL == heap_1)
	{
		HeapDestroy(heap_2);
		return MALLOC_FAIL;
	}
	if (SUCCESS != HeapPush(heap_1, array_1 + indx))
	{
			HeapDestroy(heap_2);
			HeapDestroy(heap_1);
			return PUSH_FAIL;
	}
	
	if (indx + 1 != HeapSize(heap_1))
	{
			HeapDestroy(heap_1);
			HeapDestroy(heap_2);
			return PUSH_FAIL;	
	}
	++indx;

	if (SUCCESS != HeapPush(heap_1, array_1 + indx))
	{
			HeapDestroy(heap_2);
			HeapDestroy(heap_1);
			return PUSH_FAIL;
	}
	
	if (indx + 1 != HeapSize(heap_1))
	{
			HeapDestroy(heap_1);
			HeapDestroy(heap_2);
			return PUSH_FAIL;	
	}
	++indx;
	if (SUCCESS != HeapPush(heap_1, array_1 + indx))
	{
			HeapDestroy(heap_2);
			HeapDestroy(heap_1);
			return PUSH_FAIL;
	}
	
	if (indx + 1 != HeapSize(heap_1))
	{
			HeapDestroy(heap_1);
			HeapDestroy(heap_2);
			return PUSH_FAIL;	
	}
	for (indx = 0; 7 >indx; ++indx)
	{
		if (SUCCESS != HeapPush(heap_2, array_2 + indx))
		{
			HeapDestroy(heap_2);
			HeapDestroy(heap_1);
			return PUSH_FAIL;
		}
		if (indx + 1 != HeapSize(heap_2))
		{
			HeapDestroy(heap_1);
			HeapDestroy(heap_2);
			return PUSH_FAIL;	
		}
	}
	
	/* makes sure the minimal element is the root */
	if (array_1[1] != *(int*)HeapPeek(heap_1))	
	{
			HeapDestroy(heap_2);
			HeapDestroy(heap_1);
			return PEEK_FAIL;	
	}
	if (array_2[5] != *(int*)HeapPeek(heap_2))	
	{
			HeapDestroy(heap_2);
			HeapDestroy(heap_1);
			return PEEK_FAIL;	
	}

	if (HeapIsEmpty(heap_1))
	{
		HeapDestroy(heap_2);
		HeapDestroy(heap_1);
		return ISEMPTY_FAIL;
	}
	if (HeapIsEmpty(heap_2))
	{
		HeapDestroy(heap_2);
		HeapDestroy(heap_1);
		return ISEMPTY_FAIL;
	}
	HeapDestroy(heap_2);
	HeapDestroy(heap_1);
	
	return TEST_SUCCESS;
}


test_return_status_ty TestPop(void)
{
	
	int array_1[] = {15,30,50,100,40,10,20,2,1,200};
	size_t indx = 0; 
	heap_ty *heap_1 = HeapCreate(Cmp, NULL);
	if (NULL == heap_1)
	{
		return MALLOC_FAIL;
	}
	
	for (indx = 0; 10 >indx; ++indx)
	{
		if (SUCCESS != HeapPush(heap_1, array_1 + indx))
		{
	
			HeapDestroy(heap_1);
			return PUSH_FAIL;
		}
		if (indx + 1 != HeapSize(heap_1))
		{
			HeapDestroy(heap_1);
			return PUSH_FAIL;	
		}
	}

	/* makes sure the minimal element is the root */
	
	if (array_1[8] != *(int*)HeapPeek(heap_1))	
	{
		
			HeapDestroy(heap_1);
			return PEEK_FAIL;	
	}

	HeapPop(heap_1);
	if (HeapIsEmpty(heap_1))
	{
		HeapDestroy(heap_1);
		return POP_FAIL;
	}
	if (9 != HeapSize(heap_1))
	{
		HeapDestroy(heap_1);
		return POP_FAIL;
	}
	
	if (array_1[7] != *(int*)HeapPeek(heap_1))	
	{
		
			HeapDestroy(heap_1);
			return PEEK_FAIL;	
	}
	
	HeapPop(heap_1);
	if (HeapIsEmpty(heap_1))
	{
		HeapDestroy(heap_1);
		return POP_FAIL;
	}
	if (8 != HeapSize(heap_1))
	{
		HeapDestroy(heap_1);
		return POP_FAIL;
	}
	if (array_1[5] != *(int*)HeapPeek(heap_1))	
	{
			HeapDestroy(heap_1);
			return PEEK_FAIL;	
	}
	
	HeapDestroy(heap_1);
	return TEST_SUCCESS;
}



test_return_status_ty TestRemove(void)
{
	
	int array_1[] = {15,30,50,100,40,10,20,2,1,200};
	size_t indx = 0; 
	heap_ty *heap_1 = HeapCreate(Cmp, NULL);
	if (NULL == heap_1)
	{
		return MALLOC_FAIL;
	}
	
	for (indx = 0; 10 >indx; ++indx)
	{
		if (SUCCESS != HeapPush(heap_1, array_1 + indx))
		{
	
			HeapDestroy(heap_1);
			return PUSH_FAIL;
		}
		if (indx + 1 != HeapSize(heap_1))
		{
			HeapDestroy(heap_1);
			return PUSH_FAIL;	
		}
	}
	printf("before remove : ");
	PrintHeap(heap_1);
	/* makes sure the minimal element is the root */
	if (SUCCESS != HeapRemove(heap_1, array_1 + 9, IsRemoveMatch))
	{
		HeapDestroy(heap_1);
		return REMOVE_FAIL;	
	}
	if (9 != HeapSize(heap_1))
	{
			HeapDestroy(heap_1);
			return PUSH_FAIL;	
	}
	printf("after remove : ");
	PrintHeap(heap_1);
	if (FAIL == HeapRemove(heap_1, array_1 + 9, IsRemoveMatch))
	{
		HeapDestroy(heap_1);
		return REMOVE_FAIL;	
	}
	if (9 != HeapSize(heap_1))
	{
			HeapDestroy(heap_1);
			return PUSH_FAIL;	
	}
	HeapDestroy(heap_1);
	
	return TEST_SUCCESS;
}

static bool_ty IsRemoveMatch(const void *heap_data, void *root_data)
{
    return (root_data == heap_data);
}
static int Cmp(const void *heap_data, const void *user_data, void *params)
{
	(void)params;
	return *(int*)heap_data - *(int*)user_data;
} 