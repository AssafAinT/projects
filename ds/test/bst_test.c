/*****************************************************
 * Binary_Search_Tree                                *
 * Assaf Ainhoren                                    *
 * Reviewer: Ahron Cohen                             *
 * date: 19.06.2022                                  *
 *****************************************************/

/********************************libraries includes****************************/
#include <assert.h> /* assert */

#include "bst.h"

#define UNUSED(param)  (void)param

static void CreateTest(void);
static void IsEmptyTest(void);
static void InsertTest(void);
static void GetDataTest(void);
static void FindTest(void);
static void NextTest(void);
static void SizeTest(void);
static void ForEachTest(void);
static void RemoveTest(void);
static void PrevTest(void);
int SumFunc(void *first_num, void *sum);
int CompareData(const void *data1, const void *data2 , void *params);

int main(void)
{
	CreateTest();
	IsEmptyTest();
	InsertTest();
	GetDataTest();
	FindTest();
	NextTest();
	SizeTest();
	ForEachTest();
	RemoveTest();
	PrevTest();
	return (0);
}

static void CreateTest(void)
{
	bst_ty *first_tree = BstCreate(CompareData, NULL);
	BstDestroy(first_tree);
}
static void IsEmptyTest(void)
{
	int data = 12;
	int smallest_data = 3;
	
	bst_ty *first_tree = BstCreate(CompareData, NULL);
	bst_iterator_ty new_info = NULL;
	UNUSED(new_info);
	
	assert(1 == BstIsEmpty(first_tree));
	new_info = BstInsert(first_tree, &data);
	new_info = BstInsert(first_tree, &smallest_data);
	assert(1 != BstIsEmpty(first_tree));
	BstDestroy(first_tree);
}

static void InsertTest(void)
{
	int data = 12;
	int smallest_data = 3;
	
	bst_ty *first_tree = BstCreate(CompareData, NULL);
	bst_iterator_ty new_info = NULL;
	bst_iterator_ty found_iter = NULL;
	UNUSED(new_info);
	UNUSED(found_iter);
	
	assert(1 == BstIsEmpty(first_tree));
	new_info = BstInsert(first_tree, &data);
	assert(12 == *(int *)BstGetData(new_info));
	new_info = BstInsert(first_tree, &smallest_data);
	BstDestroy(first_tree);
}

static void GetDataTest(void)
{
	int data = 12;
	
	bst_ty *first_tree = BstCreate(CompareData, NULL);
	bst_iterator_ty new_info = NULL;
	bst_iterator_ty found_iter = NULL;
	
	UNUSED(new_info);
	UNUSED(found_iter);
	
	new_info = BstInsert(first_tree, &data);
	assert(12 == *(int *)BstGetData(new_info));	
	BstDestroy(first_tree);
}

static void FindTest(void)
{
	int data = 12;
	int smallest_data = 3;
	
	bst_ty *first_tree = BstCreate(CompareData, NULL);
	bst_ty *empty_tree = BstCreate(CompareData, NULL);
	bst_iterator_ty new_info = NULL;
	bst_iterator_ty found_iter = NULL;
	
	assert(1 == BstIsEmpty(first_tree));
	new_info = BstInsert(first_tree, &data);
	assert(12 == *(int *)BstGetData(new_info));
	assert(1 != BstIsEmpty(first_tree));
	found_iter = BstFind(first_tree, &data);
	assert(12 == *(int *)BstGetData(found_iter));
	assert(NULL == BstFind(first_tree, &smallest_data));
	assert(NULL == BstFind(empty_tree, &data));
	BstDestroy(first_tree);
	BstDestroy(empty_tree);	
}

static void NextTest(void)
{
	int data = 7;
	int smallest_d = 2;
	int biggest_d = 22;
	bst_ty *first_tree = BstCreate(CompareData, NULL);
	
	bst_iterator_ty new_info = NULL;
	bst_iterator_ty next_found = NULL;
	
	new_info = BstInsert(first_tree, &smallest_d);
	new_info = BstInsert(first_tree, &biggest_d);
	new_info = BstInsert(first_tree, &data);
	
	new_info = BstBegin(first_tree);
	assert(2 == *(int *)BstGetData(new_info));
	next_found = BstGetNext(new_info);
	assert(7 == *(int *)BstGetData(next_found));
	next_found = BstGetNext(next_found);
	assert(22 == *(int *)BstGetData(next_found));
	assert(NULL == BstGetData(BstGetNext(next_found)));
	assert(NULL == BstGetData(BstEnd(first_tree)));
	
	BstDestroy(first_tree);
}
static void SizeTest(void)
{
 	int data[32] = {12, 7, 20, 4, 33, 2, 6, 1, 3, 0, 5, 10, 9, 11, 8, 17, 15,
                    19, 14, 16, 13, 18, 25, 23, 22, 21, 24, 28, 27, 26, 30, 29};
	
	int insertion_arr[] = {3,8,22,9};
	size_t tree_size = 4;
	size_t insert_size = 0;
	bst_ty *big_tree = BstCreate(CompareData, NULL);
	bst_ty *first_tree = BstCreate(CompareData, NULL);
	
	bst_iterator_ty big_iter = NULL;
	bst_iterator_ty new_info = NULL;
	UNUSED(big_iter);
	UNUSED(new_info);
		
	for ( ; insert_size < tree_size; ++insert_size)
	{
		new_info = BstInsert(first_tree, &insertion_arr[insert_size]);
	}
	for ( insert_size = 0; insert_size < 32; ++insert_size)
	{
		big_iter = BstInsert(big_tree, &data[insert_size]);
	}
	assert(tree_size == BstSize(first_tree));
	assert(32 == BstSize(big_tree));
	BstDestroy(big_tree);
	BstDestroy(first_tree);
}

static void ForEachTest(void)
{
	size_t insert_size = 0;
	int sum = 0;
	int data[33] = {12, 7, 20, 4, 33, 2, 6, 1, 3, 0, 5, 10, 9, 11, 8, 17, 15,
                    19, 14, 16, 13, 18, 25,31, 23, 22, 21, 24, 28, 27, 26, 30, 29};
    
    bst_ty *big_tree = BstCreate(CompareData, NULL);
    bst_iterator_ty big_iter = NULL;
    UNUSED(big_iter);
    for ( insert_size = 0; insert_size < 33; ++insert_size)
	{
		big_iter = BstInsert(big_tree, &data[insert_size]);
	}
	assert(0 == BstForEach(BstBegin(big_tree), BstEnd(big_tree), SumFunc, &sum));
	BstDestroy(big_tree);
}

static void PrevTest(void)
{
	int data[32] = {12, 7, 20, 4, 33, 2, 6, 1, 3, 0, 5, 10, 9, 11, 8, 17, 15,
                    19, 14, 16, 13, 18, 25, 23, 22, 21, 24, 28, 27, 26, 30, 29};
	size_t desired_size = 32;
	size_t insert_size = 0;
	bst_ty *big_tree = BstCreate(CompareData, NULL);
	
	bst_iterator_ty big_iter = NULL;
    
    for ( insert_size = 0; insert_size < desired_size; ++insert_size)
	{
		big_iter = BstInsert(big_tree, &data[insert_size]);
	}
	assert(desired_size == BstSize(big_tree));
	
	assert(29 == *(int *)BstGetData(big_iter));
	big_iter = BstGetPrev(big_iter);
	assert(28 == *(int *)BstGetData(big_iter));
	assert(desired_size == BstSize(big_tree));
	big_iter = BstGetPrev(big_iter);
	assert(27 == *(int *)BstGetData(big_iter));
	big_iter = BstBegin(big_tree);
	/* check to see if NULL back */
	big_iter = BstGetPrev(big_iter);
	assert(NULL == (big_iter));
	BstDestroy(big_tree);
}
static void RemoveTest(void)
{

	int insertion_arr[] = {5,4,22,9};
	size_t insert_size = 0;
	size_t tree_size = 4;
	bst_ty *first_tree = BstCreate(CompareData, NULL);
	
	bst_iterator_ty new_info = NULL;
	
	for ( ; insert_size < tree_size ; ++insert_size)
	{
		new_info = BstInsert(first_tree, &insertion_arr[insert_size]);
	}
	assert(tree_size == BstSize(first_tree));
	
	new_info = BstFind(first_tree, &insertion_arr[3]);
	assert(9 == *(int *)BstRemove(new_info));
	assert(tree_size -1  == BstSize(first_tree));
	new_info = BstBegin(first_tree);
	new_info = BstRemove(new_info);
	assert(tree_size -2  == BstSize(first_tree));
	new_info = BstBegin(first_tree);
	new_info = BstRemove(new_info);
	assert(tree_size -3  == BstSize(first_tree));
	
	BstDestroy(first_tree);
}
int CompareData(const void *data1, const void *data2 , void *params)
{
	UNUSED(params);
	
	return ((*(int *)(data1)) - (*(int *)data2));
}

int SumFunc(void *first_num, void *sum)
{
	*((int *)sum) += *((int *)first_num);
	
	return (0);
}
