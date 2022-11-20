#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include <stdio.h> /* printf */
#include "stack.h" 
#include "slist.h"


struct min_stack
{
	slist_ty *min_list;
	stack_ty *stack;
};

typedef struct min_stack min_stack_ty; 

/* creates the stack */
min_stack_ty *MinStackCreate(size_t element_amount, size_t size_of_element);
/* checking if the popped element is the same at the current min */
void CheckBeforePop(min_stack_ty *min_stack);
/* destroy the min stack */
void DestroyMinStack(min_stack_ty *min_stack);
/* checking if the given element is lower than the current one in the stack,
if it is, it will go in the min stack */
void InsertMinElementToMinStack(min_stack_ty *min_stack, void *element);
/* peek the min element */
void *PeekMin(min_stack_ty *min_stack);

int main(void)
{
	int first_data = 2;
	int second_data = 6;
	int third_data = -1;
	int forth_data = 7;
	
	min_stack_ty *my_stack = MinStackCreate(10, 4);
	
	InsertMinElementToMinStack(my_stack, &first_data);
	InsertMinElementToMinStack(my_stack, &second_data);
	InsertMinElementToMinStack(my_stack, &third_data);
	InsertMinElementToMinStack(my_stack, &forth_data);
	
	printf("Min element is: [%d]\n", *(int *)PeekMin(my_stack));
	
	CheckBeforePop(my_stack);
	CheckBeforePop(my_stack);
	printf("Min element is: [%d]\n", *(int *)PeekMin(my_stack));
	DestroyMinStack(my_stack);
	return (0);
}

min_stack_ty *MinStackCreate(size_t element_amount, size_t size_of_element)
{
	
	min_stack_ty *min_stack = (min_stack_ty *)malloc(sizeof(min_stack_ty));
	if (NULL == min_stack)
	{
		return (NULL);
	}
	
	min_stack->min_list = SlistCreate();
	if (NULL == min_stack->min_list)
	{
		free(min_stack);
		return NULL;
	}
	min_stack->stack = StackCreate(element_amount, size_of_element);
	if (NULL == min_stack->stack)
	{
		free(min_stack->min_list);
		free(min_stack);
		return (NULL);
	}
	return (min_stack);
}

void DestroyMinStack(min_stack_ty *min_stack)
{
	SlistDestroy(min_stack -> min_list);
	StackDestroy(min_stack -> stack);
	free(min_stack);
	
}

void InsertMinElementToMinStack(min_stack_ty *min_stack, void *element)
{
	if ((*(int *)SlistGetData(SlistBegin(min_stack->min_list))) > 
							 (*(int *)element))
	{
		SlistInsertBefore(SlistBegin(min_stack->min_list), element);
	}
	
	StackPush(min_stack -> stack, element);
		
}



void CheckBeforePop(min_stack_ty *min_stack)
{
	if ((*(int *)SlistGetData(SlistBegin(min_stack->min_list))) == 
		(*(int *)StackPeek(min_stack->stack)))
	{
		
		SlistRemove(SlistBegin(min_stack -> min_list));
	}
	
	StackPop(min_stack -> stack);
}

void *PeekMin(min_stack_ty *min_stack)
{
	assert(0 == SlistIsEmpty(min_stack->min_list));

	return (SlistGetData(SlistBegin(min_stack -> min_list)));
}

