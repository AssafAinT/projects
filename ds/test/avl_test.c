/*****************************************************
 * Avl                                               *
 * Assaf Ainhoren                                    *
 * Reviewer: Ofir Krisple                            *
 * date: 27.07.2022                                  *
 *****************************************************/

/********************************libraries includes****************************/
#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include <stdlib.h> /* free */
#include "avl.h"

#define UNUSED(param)  (void)param

int SumFunc(void *first_num, void *sum);
int CompareData(const void *data1, const void *data2 , void *params);
int PrintFunction(void *data, void *params);
static void RotationTest(void);
static void CreateTest(void);
static void IsEmptyTest(void);
static void InsertTest(void);
static void SizeTest(void);
static void HightTest(void);
static void FindTest(void);
static void ForEachTest(void);
static void RemoveTest(void);

int main(void)
{
	RotationTest();
	CreateTest();
	IsEmptyTest();
	SizeTest();
	InsertTest();
	HightTest();
	FindTest();
	ForEachTest();
	RemoveTest();
	printf("------------------------------You successed!--------------------\n");
	return (0);
}
static void RotationTest(void)
{
	int data_1 = 8;
	int data_2 = 9;
	int data_3 = 10;
	int data_4 = 5;
	int data_5 = 6;
	int data_6 = 12;
	int data_7 = 11;
	avl_ty *avl_test = AvlCreate(CompareData, NULL);
	printf("--------------------------------Rotation_test------------------\n");
	AvlInsert(avl_test, &data_1);
	AvlInsert(avl_test, &data_2);
	AvlInsert(avl_test, &data_3);
	AvlInsert(avl_test, &data_4);
	AvlInsert(avl_test, &data_5);
	AvlInsert(avl_test, &data_6);
	AvlInsert(avl_test, &data_7);
	#ifndef NDEBUG
	TreePrint(avl_test);
	#endif
	printf("------------------------------Rotation test done----------------\n");
	AvlDestroy(avl_test);
}

static void CreateTest(void)
{
	avl_ty *first_avl = AvlCreate(CompareData, NULL);
	assert(TRUE == AvlIsEmpty(first_avl));
	AvlDestroy(first_avl);
	printf("-----------------------------Create test done------------------\n");
}

static void IsEmptyTest(void)
{
	avl_ty *first_avl = AvlCreate(CompareData, NULL);
	assert(TRUE == AvlIsEmpty(first_avl));
	assert(0 == AvlSize(first_avl));
	AvlDestroy(first_avl);
	printf("-----------------------------IsEmpty test done------------------\n");
}


static void InsertTest(void)
{
	int i = 0;
    int data[31] = {12, 7, 20, 4, 10, 2, 6, 1, 3, 0, 5, 9, 11, 8, 17, 15,
                19, 14, 16, 13, 18, 25, 23, 22, 21, 24, 28, 27, 26, 30, 29};
                    
	 /*
                           12
                  ___...--'  `----....._____
                 7                          20
              _.' `-._                 __.-'  `--...___
             4        10              17               25
           _' `_     /  \         _.-'  `_         _.-'  `-._
          2     6   9    11      15       19      23         28
         / \   /   /            /  \     /       /  \       /  `_
        1   3 5   8            14   16  18      22   24    27    30
       /                      /                /          /     /
      0                      13               21         26    29
 
    */
    
    avl_ty *new_avl = AvlCreate(CompareData, NULL);
    
    for (i = 0 ; i < 31 ; ++i)
    {
        assert(0 == AvlInsert(new_avl , &data[i]));
    }
	#ifndef NDEBUG
	TreePrint(new_avl);
	#endif
    AvlDestroy(new_avl);
    printf("-----------------------------Insert Completed!------------------\n");
}

static void SizeTest(void)
{
	int i = 0;
    int data[31] = {12, 7, 20, 4, 10, 2, 6, 1, 3, 0, 5, 9, 11, 8, 17, 15,
                19, 14, 16, 13, 18, 25, 23, 22, 21, 24, 28, 27, 26, 30, 29};
                    
    
    avl_ty *new_avl = AvlCreate(CompareData, NULL);
    
    assert(0 == AvlSize(new_avl));
    for (i = 0 ; i < 31 ; ++i)
    {
        AvlInsert(new_avl , &data[i]);
    }
    assert(31 == AvlSize(new_avl));
    AvlDestroy(new_avl);
}
static void HightTest(void)
{
	int i = 0;
    int data[31] = {12, 7, 20, 4, 10, 2, 6, 1, 3, 0, 5, 9, 11, 8, 17, 15,
                19, 14, 16, 13, 18, 25, 23, 22, 21, 24, 28, 27, 26, 30, 29};
                    
    
    avl_ty *new_avl = AvlCreate(CompareData, NULL);
    
    for (i = 0 ; i < 31 ; ++i)
    {
        AvlInsert(new_avl , &data[i]);
    }
 	assert(5 == AvlHeight(new_avl));
    AvlRemove(new_avl, &data[20]);
    AvlRemove(new_avl, &data[24]);
    AvlRemove(new_avl, &data[29]);
    AvlRemove(new_avl, &data[28]);
    AvlRemove(new_avl, &data[26]);
    AvlRemove(new_avl, &data[25]);
    assert(4 == AvlHeight(new_avl));
    AvlDestroy(new_avl);
    printf("---------------------------size test completed!--------------\n\n");
}

static void FindTest(void)
{
	int i = 0;
	int data_missing = 99;
	int data_missing2 = 105;
	int data_missing3 = 7;
    int data[31] = {12, 7, 20, 4, 10, 2, 6, 1, 3, 0, 5, 9, 11, 8, 17, 15,
                19, 14, 16, 13, 18, 25, 23, 22, 21, 24, 28, 27, 26, 30, 29};
                    
    
    avl_ty *new_avl = AvlCreate(CompareData, NULL);
    
    for (i = 0 ; i < 31 ; ++i)
    {
        AvlInsert(new_avl , &data[i]);
    }
    assert(SUCCESS == AvlFind(new_avl, &data[30]));
    assert(SUCCESS ==  AvlFind(new_avl, &data[2]));
    assert(FAIL ==  AvlFind(new_avl, &data_missing));
    assert(FAIL ==  AvlFind(new_avl, &data_missing2));
    assert(SUCCESS ==  AvlFind(new_avl, &data_missing3));
    
    AvlDestroy(new_avl);
    printf("---------------------------find test completed!--------------\n\n");
}

static void ForEachTest(void)
{
	int i = 0;
    int data[31] = {12, 7, 20, 4, 10, 2, 6, 1, 3, 0, 5, 9, 11, 8, 17, 15,
                19, 14, 16, 13, 18, 25, 23, 22, 21, 24, 28, 27, 26, 30, 29};
                    
    
    avl_ty *new_avl = AvlCreate(CompareData, NULL);
    
    for (i = 0 ; i < 31 ; ++i)
    {
        AvlInsert(new_avl , &data[i]);
    }
    printf("in tree by post_order:\n");
    AvlForEach(new_avl, PrintFunction, NULL, POST_ORDER);
    printf("\n");
    printf("\nin tree by in_order:\n");
    AvlForEach(new_avl, PrintFunction, NULL, INORDER);
    printf("\n");
    printf("\nin tree by pre_order:\n");
    AvlForEach(new_avl, PrintFunction, NULL, PREORDER);
    printf("\n");
    
    AvlDestroy(new_avl);
    printf("-----------------------ForEach test completed!--------------\n\n");
}

static void RemoveTest(void)
{
	int i = 0;
	int data_not_exist = 120;
	int data2_not_exist = 1234567;
    int data[31] = {12, 7, 20, 4, 10, 2, 6, 1, 3, 0, 5, 9, 11, 8, 17, 15,
                19, 14, 16, 13, 18, 25, 23, 22, 21, 24, 28, 27, 26, 30, 29};
                    
    
    avl_ty *new_avl = AvlCreate(CompareData, NULL);
    
    for (i = 0 ; i < 31 ; ++i)
    {
        AvlInsert(new_avl , &data[i]);
    }
	printf("------------------------------remove test----------------------\n");
	printf("------------------------------tree before remove---------------\n");
	#ifndef NDEBUG
	TreePrint(new_avl);
	#endif
    assert(5 == AvlHeight(new_avl));
    AvlRemove(new_avl, &data[20]);
    AvlRemove(new_avl, &data[24]);
    AvlRemove(new_avl, &data[29]);
    AvlRemove(new_avl, &data[28]);
    AvlRemove(new_avl, &data[26]);
    AvlRemove(new_avl, &data[25]);
    assert(4 == AvlHeight(new_avl));
    AvlRemove(new_avl, &data[2]);
    AvlRemove(new_avl, &data[4]);
    AvlRemove(new_avl, &data[11]);
    printf("------------------------------tree after remove---------------\n");
    #ifndef NDEBUG
	TreePrint(new_avl);
	#endif
    /* trying to remove something that do not exist */
    AvlRemove(new_avl, &data_not_exist);
    AvlRemove(new_avl, &data2_not_exist);
    AvlDestroy(new_avl);
    printf("---------------------remove test completed!---------------------\n");
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

int PrintFunction(void *data, void *params)
{
    UNUSED(params);
    
    printf("%d ", *(int *)data);
    return 0;
}
