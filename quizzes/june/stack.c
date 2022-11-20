/*****************************************************
 * WS11                                              *
 * Assaf Ainhoren                                    *
 * Reviewer: Ester Shpoker                           *
 * date: 05.06.2022                                  *
 *****************************************************/
 
/********************************libraries includes****************************/
#include <stddef.h> /* size_t */
#include <stdlib.h> /*malloc */
#include <assert.h> /*assert */
#include <string.h> /*memcpy */
#include "stack.h" 

/********************************stack defining********************************/
struct stack 
{
	char *top;
	char *stack_base;
	size_t element_amount;  
	size_t size_of_element; 
	
};

/**************************stack function defining*****************************/

stack_ty *StackCreate(size_t element_amount, size_t size_of_element)
{
	stack_ty *new_stack = (stack_ty *)malloc(sizeof(stack_ty));
	if (NULL == new_stack)
	{
		return (NULL);
	}
	
	new_stack->element_amount = element_amount;
	new_stack->size_of_element = size_of_element;
	
	new_stack->stack_base = (char *)malloc(new_stack->element_amount *
						  (new_stack->size_of_element));
	
	if (NULL == new_stack->stack_base)
	{
		free(new_stack);
		return (NULL);
	}
	
	new_stack->top = new_stack->stack_base;
	
	return (new_stack);
}

void StackDestroy(stack_ty *stack)
{
	assert(NULL != stack);
	
	free(stack->stack_base);
	
	free(stack);
	stack = NULL;

}

void StackPop(stack_ty *stack)
{
	assert(NULL != stack);
	/*assert(StackIsEmpty(stack) > 0);*/
	{
		stack->top -= stack->size_of_element;		
	}

}

void StackPush(stack_ty *stack, const void *element)
{
	assert(NULL != stack);
	assert(StackSize(stack)!= stack->element_amount);
	
	memcpy(stack->top, element, stack->size_of_element);
	
	stack->top += stack->size_of_element;
}

void *StackPeek(const stack_ty *stack)
{
	void *top_element = (stack->top) - stack->size_of_element;
	
	assert(NULL != stack);
	/*assert(StackIsEmpty(stack) > 0);*/
	return (top_element);
}

size_t StackSize(const stack_ty *stack)
{
	assert(NULL != stack);
	
	return (((stack->top) - (stack->stack_base))/ (stack ->size_of_element));
}

int StackIsEmpty(const stack_ty *stack)
{
	assert(NULL != stack);
	
	return (!!(stack->top - stack->stack_base));
}

size_t StackCapacity(const stack_ty *stack)
{
	assert(NULL != stack);
	
	return (stack->element_amount * stack->size_of_element);

}
