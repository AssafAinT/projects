/*****************************************************
 * Recursion                                         *
 * Assaf Ainhoren                                    *
 * Reviewer: Ester Shpoker                           *
 * date: 18.07.2022                                  *
 *****************************************************/

/********************************libraries includes****************************/
#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include <string.h> /* string funcs */

#include "recursion.h"
/*static int counter = 0;*/
static void FibonacciTest(void);
static void StrLenTest(void);
static void StrCmpTest(void);
static void StrCpyTest(void);
static void StrCatTest(void);
static void TestFlipList(void);
static void *PrintListInt(node_ty *node);
static void StrStrTest(void);
static void StackSortTest(void);

/*static void Recurse(void);*/
static void Iter(void);
int main(void)
{
	/*Recurse();
	Iter();*/
	StrLenTest();
	FibonacciTest();
	StrCmpTest();
	StrCpyTest();
	StrCatTest();
	TestFlipList();
	StrStrTest();
	StackSortTest();
	return (0);
}

/*
static void Recurse(void)
{
	++counter;
	printf("%d FunctionCalls\n", counter);
	
	Recurse();
}*/
/*
static void Iter(void)
{	
	static unsigned int iter_counter = 0;
	while(1)
	{
		++iter_counter;
		printf("%d Iteravtive FunctionCalls\n", iter_counter);
	}
}*/

static void FibonacciTest(void)
{
    assert(4181 == FibonacciIterative(19));
    assert(4181 == Fibonacci(19));
    assert(3 == FibonacciIterative(4));
    assert(3 == Fibonacci(4));
    assert(5 == FibonacciIterative(5));
    assert(5 == Fibonacci(5));
    assert(2 == FibonacciIterative(3));
    assert(2 == Fibonacci(3));
    assert(1 == FibonacciIterative(2));
    assert(1 == Fibonacci(2));
    assert(1 == FibonacciIterative(1));
    assert(1 == Fibonacci(1));
    assert(0 == FibonacciIterative(0));
    assert(0 == Fibonacci(0));
    assert(-1 == Fibonacci(-1));
	
}

static void StrLenTest(void)
{
	assert( 5 == StrLen("assaf"));
	assert( 0 == StrLen(""));
	assert( 1 == StrLen(" "));
}

static void StrCmpTest(void)
{
	
	assert(0 < StrCmp("assaf", "ass"));
	assert(0 > StrCmp("ass", "assaf"));
	assert(0 == StrCmp("", ""));
	assert(0 == StrCmp(" ", " "));
}

static void TestFlipList(void)
{
    int data1 = 1;
    int data2 = 3;
    int data3 = 7;
    int data4 = 5;
    
    node_ty *pt = CreateNewNode(&data1);
    node_ty *iterator = pt;
    

    InsertNode(iterator,&data2);
    iterator = NextNode(iterator);
    assert(3 == *(int *)NodeGetData(iterator));
    
    InsertNode(iterator,&data3);
    iterator = NextNode(iterator);
    assert(7 == *(int *)NodeGetData(iterator));

    InsertNode(iterator,&data4);
    iterator = NextNode(iterator);
    assert(5 == *(int *)NodeGetData(iterator));
    
    PrintListInt(pt);
    pt = FlipList(pt);
    assert(5 == *(int *)NodeGetData(iterator));
    iterator = NextNode(iterator);
    assert(7 == *(int *)NodeGetData(iterator));
    iterator = NextNode(iterator);
    assert(3 == *(int *)NodeGetData(iterator));
    iterator = NextNode(iterator);
    assert(1 == *(int *)NodeGetData(iterator));
    PrintListInt(pt);
    DestroyNodeList(pt);
}

/************PrintList************/

static void *PrintListInt(node_ty *node)
{
    assert(NULL != node);

    printf("list : ");
    while (NULL != node)
    {
        printf("%d" , *(int *)NodeGetData(node));
        node = node->next;
    }
    printf("\n");
    
    return (node);
}

static void StrCpyTest(void)
{
	char *string_original = "boom-pam";
	char *string_original1 = "playa_del_majorca";
	char string_to_insert[10] = "";
	char string_to_insert1[20] = "";
	char string_to_insert2[30] = "";
	StrCpy(string_to_insert, string_original);
	puts(string_to_insert);
	StrCpy(string_to_insert1, string_original1);
	puts(string_to_insert1);
	StrCpy(string_to_insert2, "bloopliblopplalala123\n");
	puts(string_to_insert2);
}

static void StrCatTest(void)
{
	char *string_original = "boom-pam";
	char string_to_be_filled[20] = "123";
	char *string_original1 = "playa_del_majorca";
	char string_to_be_filled1[33] = "i'm in ";
	StrCat(string_to_be_filled, string_original);
	puts(string_to_be_filled);
	StrCat(string_to_be_filled1, string_original1);
	puts(string_to_be_filled1);
}

static void StrStrTest(void)
{
	char string7[100] = "assaf";
	char string8[100] = "ass";
	char string1[15] = "balfooonfor";
	char string2[15] = "for";
	char string3[10] = "rada";
	char string4[10] = "shada";
	assert(strstr(string7,string8) == StrStr(string7,string8));
	assert(strstr(string1,string2) == StrStr(string1,string2));
	assert(strstr(string3,string4) == StrStr(string3,string4));

}

static void StackSortTest(void)
{
 	int data1 = 12;
	int data2 = 18;
	int data3 = -1;
	int data4 = 6;
	stack_ty *new_stack = StackCreate(4, sizeof(int));
	StackPush(new_stack, &data1);
	assert(12 == *(int *)StackPeek(new_stack));
	StackPush(new_stack, &data3);
	assert(-1 == *(int *)StackPeek(new_stack));
	StackPush(new_stack, &data4);
	assert(6 == *(int *)StackPeek(new_stack));
	StackPush(new_stack, &data2);
	assert(18 == *(int *)StackPeek(new_stack));
	
	StackSort(new_stack);
	assert(18 == *(int *)StackPeek(new_stack));
	StackPop(new_stack);
	assert(12 == *(int *)StackPeek(new_stack));
	StackPop(new_stack);
	assert(6 == *(int *)StackPeek(new_stack));
	StackPop(new_stack);
	assert(-1 == *(int *)StackPeek(new_stack));

	
	StackDestroy(new_stack);
}
