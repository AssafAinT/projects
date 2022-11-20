/*****************************************************
 * Recursion                                         *
 * Assaf Ainhoren                                    *
 * Reviewer: Ester Shpoker                           *
 * date: 18.07.2022                                  *
 *****************************************************/

/********************************libraries includes****************************/
#include <assert.h> /* assert */
#include <stddef.h> /* size_t */
#include <string.h> /* strncmp */
#include  "recursion.h"

static const int last_element = 1;
static void InsertSort(stack_ty *stack,int copy_top_element);

int Fibonacci(int element_index)
{
	if (element_index <= last_element)
	{
		return (element_index);
	}
	return (Fibonacci(element_index-1)+Fibonacci(element_index-2));
}

int FibonacciIterative(int element_index)
{
	int index = 3;
	int fib1 = 0;
	int fib2 = 1;
	int fib_n = fib1 + fib2;
	
	if (0 == element_index)
	{
		return 0;
	}
	
	for ( ; index <= element_index; ++index)
	{
		fib1 = fib2;
		fib2 = fib_n;
		fib_n = fib1 +fib2;
	}
	return (fib_n);
}

node_ty *FlipList(node_ty *node)
{
	static node_ty *next_node = NULL;
	
	if (node == NULL || node->next == NULL)
	{
            return node;
	}
	next_node = FlipList(node->next);
	node->next->next = node;
	node->next = NULL;

	return(next_node);	
}


size_t StrLen(const char *str)
{
	assert (NULL != str);
	if ('\0' == *str)
	{
		return (0);
	}
	return (1 + StrLen(++str));
}

int StrCmp( const char *str1, const char *str2)
{
	assert (NULL != str1);
	assert (NULL != str2);
	
	if (('\0' == *str1) || (*str1 != *str2))
	{
		return (*str1 - *str2);
	}
	else
	{
		return (StrCmp(++str1, ++str2));
	}
}

char *StrCpy(char *destination, const char *source)
{
	assert( NULL != destination );
	assert( NULL != source );
	
	if ('\0' == *source)
	{	
		*destination = '\0';
		return(destination);
	}
	*destination = *source;
	return (StrCpy(++destination,++source));
}

char *StrCat(char *destination, const char *src)
{	
	assert( NULL != destination);
	assert( NULL != src);
	
	if ('\0' == *destination)
	{
		return(StrCpy(destination, src));
	}
	

	return (StrCat(++destination, src));
}

char *StrStr(const char *haystack, const char *needle)
{
	assert(NULL != haystack);
	assert(NULL != needle);
	 
	if ('\0' == *haystack)
	{ 
		return NULL;
	} 
	else if (0 == strncmp(haystack, needle, strlen(needle)))
	{ 
		return (char *)haystack;
	}
	else
	{ 
		return(StrStr(++haystack, needle));
	} 
}
void StackSort(stack_ty *stack)
{
	/*SortStack*/
	if (!StackIsEmpty(stack))
	{
		int copy_top_element = *(int *)StackPeek(stack);
		StackPop(stack);
		StackSort(stack);
		InsertSort(stack, copy_top_element);
	}
}
static void InsertSort(stack_ty *stack, int copy_top_element)
{
	if (StackIsEmpty(stack) || copy_top_element > *(int *)StackPeek(stack))
	{
		StackPush(stack, &copy_top_element);
	}
	else
	{
		int another_copy = *(int *)StackPeek(stack);
		StackPop(stack);
		InsertSort(stack, copy_top_element);
		StackPush(stack, &another_copy);
	}
}

