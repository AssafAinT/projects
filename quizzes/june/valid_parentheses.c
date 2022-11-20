/********************************libraries includes****************************/
#include <stdio.h> /*printf */
#include <stddef.h> /* size_t */
#include <stdlib.h> /*malloc */
#include <assert.h> /*assert */
#include <string.h> /*strlen */

#include "../../ds/include/stack.h"
/********************************stack defining********************************/
struct stack 
{
	char *top;
	char *stack_base;
	size_t element_amount;  
	size_t size_of_element; 
	
};

int main()
{
	char string[14] = "[()](){[()]()}";
	char string2[12] = "[(](){[()]()";
	char string3[4] = "[(]";
	char string4[2] = "(";
	stack_ty *parentheses = StackCreate(14,1);
	stack_ty *parentheses2 = StackCreate(12,1);
	stack_ty *parentheses3 = StackCreate(4,1);
	stack_ty *parentheses4 = StackCreate(2,1);
	size_t len1 = strlen(string);
	size_t len2 = strlen(string2);
	size_t len3 = strlen(string3);
	size_t len4 = strlen(string4);
	
  	assert(1==IsValidParentheses(parentheses, string, len1));
  	assert(0==IsValidParentheses(parentheses2, string2, len2));
	assert(0==IsValidParentheses(parentheses3, string3, len3));
	assert(0==IsValidParentheses(parentheses4, string4, len4));
	

	StackDestroy(parentheses);
	StackDestroy(parentheses2);
	StackDestroy(parentheses3);
	StackDestroy(parentheses4);
	return 0;
}
/************************************function declaration**********************/
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
	assert(StackIsEmpty(stack) != 1);
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
	assert(StackIsEmpty(stack) != 1);
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
	
	return ((stack->top==stack->stack_base));
}

size_t StackCapacity(const stack_ty *stack)
{
	assert(NULL != stack);
	
	return (stack->element_amount * stack->size_of_element);

}

int checkPair(char string1,char string2)
{
    return (( string1 == '(' && string2 == ')' ) ||
			( string1 == '[' && string2 == ']' ) ||
			( string1 == '{' && string2 == '}' ));
}

int IsValidParentheses(stack_ty *stack, char *string, size_t len)
{
    size_t i = 0;
    
    for (; i < len; ++i)  
    { 
        if (string[i] == '(' || string[i] == '[' || string[i] == '{')  
        {  
          StackPush(stack,&string[i]);
        } 
        else
        {
        	if (1 == StackIsEmpty(stack)) 
        	{
           		return 0;
        	}
        	else if (checkPair(*(char *)StackPeek(stack),string[i]))
        	{
            	StackPop(stack);
            	continue;
        	}
        	/* in case no matching pair */
	        return 0;
        }
    }   
	return (1);

}

