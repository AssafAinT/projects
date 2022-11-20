/*****************************************************
 * WS11                                              *
 * Assaf Ainhoren                                    *
 * Reviewer: Ester Shpoker                           *
 * date: 05.06.2022                                  *
 *****************************************************/
#include <stdio.h> /*printf*/
#include <stddef.h> /*size_t*/

#include "stack.h"

int StackTest1();
int StackTest2();
int StackTest3();
int StackTest4();


int main(void)
{
	if(0 != StackTest1())
	{
		return (1);
	}
	
	if(0 != StackTest2())
	{
		return (1);
	}
	if(0 != StackTest3())
	{
		return (1);
	}
	if(0 != StackTest4())
	{
		return (1);
	}

	
	return (0);
}


int StackTest1(void)
{
	size_t size_of_element = sizeof(double);
	size_t amount_of_elements = 6;
	size_t stack_capacity = 0;
	size_t size_of_current_stack = 0;
	
	double element_1 = 111111.212121;
	double element_2 = 2355789.1;
	double element_3 = 40101023;
	double element_4 = 1.234321;
	double element_5 = 123432.11;
	double element_6 = 123432.11;
	
	stack_ty *first_stack = StackCreate(amount_of_elements, size_of_element);
	
	stack_capacity = StackCapacity(first_stack);
	printf("the stack capacity: %ld\n\n", stack_capacity);
	
	StackPush(first_stack, &element_1);
	StackPush(first_stack, &element_2);
	StackPush(first_stack, &element_3);
	StackPush(first_stack, &element_4);
	StackPush(first_stack, &element_5);
	StackPush(first_stack, &element_6);
	
	
	for ( ;0 != amount_of_elements; --amount_of_elements)
	{
		printf("%f\n", *(double *)StackPeek(first_stack));
		StackPop(first_stack);
		
		size_of_current_stack = StackSize(first_stack);
		printf("the size of stack is: %ld\n", size_of_current_stack);
		printf("is empty: %d\n", StackIsEmpty(first_stack));
	}
	
	StackDestroy(first_stack);
	
	return (0);
}

int StackTest2(void)
{
	size_t size_of_element = sizeof(int);
	size_t amount_of_elements = 4;
	size_t stack_capacity = 0;
	size_t size_of_current_stack = 0;
	
	int element_1 = -23211;
	int element_2 = 22321312;
	int element_3 = -34;
	int element_4 = 0;
	
	stack_ty *first_stack = StackCreate(amount_of_elements, size_of_element);
	
	stack_capacity = StackCapacity(first_stack);
	printf("\nthe stack capacity: %ld\n\n", stack_capacity);
	
	StackPush(first_stack, &element_1);
	StackPush(first_stack, &element_2);
	StackPush(first_stack, &element_3);
	StackPush(first_stack, &element_4);
	
	
	for ( ;0 != amount_of_elements; --amount_of_elements)
	{
		printf("%d\n", *(int *)StackPeek(first_stack));
		StackPop(first_stack);
		
		size_of_current_stack = StackSize(first_stack);
		printf("the size of stack is: %ld\n", size_of_current_stack);
		printf("is empty: %d\n", StackIsEmpty(first_stack));
	}
	
	StackDestroy(first_stack);
	return (0);
}

int StackTest3(void)
{
	size_t size_of_element = sizeof(char);
	size_t amount_of_elements = 4;
	size_t stack_capacity = 0;
	size_t size_of_current_stack = 0;
	
	char element_1 = 'a';
	char element_2 = '-';
	char element_3 = 'b';
	char element_4 = '/';
	
	stack_ty *first_stack = StackCreate(amount_of_elements, size_of_element);
	
	stack_capacity = StackCapacity(first_stack);
	printf("\nthe stack capacity: %ld\n\n", stack_capacity);
	
	StackPush(first_stack, &element_1);
	StackPush(first_stack, &element_2);
	StackPush(first_stack, &element_3);
	StackPush(first_stack, &element_4);
	
	
	for ( ;0 != amount_of_elements; --amount_of_elements)
	{
		printf("%c\n", *(char *)StackPeek(first_stack));
		StackPop(first_stack);
		
		size_of_current_stack = StackSize(first_stack);
		printf("the size of stack is: %ld\n", size_of_current_stack);
		printf("is empty: %d\n", StackIsEmpty(first_stack));
	}
	
	StackDestroy(first_stack);
	
	return (0);
}

int StackTest4(void)
{
	size_t size_of_element = sizeof(size_t);
	size_t amount_of_elements = 4;
	size_t stack_capacity = 0;
	size_t size_of_current_stack = 0;
	
	size_t element_1 = 65535;
	size_t element_2 = 0;
	size_t element_3 = 12121;
	size_t element_4 = 122212221;
	
	stack_ty *first_stack = StackCreate(amount_of_elements, size_of_element);
	
	stack_capacity = StackCapacity(first_stack);
	printf("\nthe stack capacity: %ld\n\n", stack_capacity);
	
	StackPush(first_stack, &element_1);
	StackPush(first_stack, &element_2);
	StackPush(first_stack, &element_3);
	StackPush(first_stack, &element_4);
	
	
	for ( ;0 != amount_of_elements; --amount_of_elements)
	{
		printf("%lu\n", *(size_t *)StackPeek(first_stack));
		StackPop(first_stack);
		
		size_of_current_stack = StackSize(first_stack);
		printf("the size of stack is: %ld\n", size_of_current_stack);
		printf("is empty: %d\n",StackIsEmpty(first_stack) );
	}
	
	StackDestroy(first_stack);
	
	return(0);
}
