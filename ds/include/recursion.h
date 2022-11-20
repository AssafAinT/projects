/*****************************************************
 * Recursion                                         *
 * Assaf Ainhoren                                    *
 * Reviewer: Ester Shpoker                           *
 * date: 18.07.2022                                  *
 *****************************************************/

/********************************libraries includes****************************/
#ifndef __ILRD_OL127_128_RECURSION_H__
#define __ILRD_OL127_128_RECURSION_H__

#include "node.h"
#include "stack.h"
/*****************************************************
* Description: Find N element in fib sequence        *
* Params: element_index - the element to find        *
* return value: Upon succes:N element in fib sequence*
				Sending nums smaller than 1          *
				cause undefined behaviour            *
* Complexity:                                        *
* Time - O(2^n).                                     *
* Auxilary Space -best case  avg case  worst         *
*                 O(n).       o(logn)   O(n)         *
*****************************************************/
int Fibonacci(int element_index);
/*********************************************************
* Description: Find N element in fib sequence iterative  *
* Params: element_index - the element to find            *
* return value: Upon succes:N element in fib sequence    *
				Sending nums smaller than 1              *
				cause undefined behaviour                *
* Complexity:                                            *
* Time - O(n).                                           *
* Space - O(n)                                           *
*********************************************************/
int FibonacciIterative(int element_index);
/*****************************************************
* Description: Reverse/Flip the linked list          *
* Params:                                            *
*        node - the node to start flip from          *
* return value: The reversed linked list             *
				sending invalid list                 *
				cause undefined behaviour            *
* Complexity:                                        *
* Time - O(n).                                       *
* Space - O(1)                                       *
*****************************************************/
node_ty *FlipList(node_ty *node);
/******************************************************
* Description: computing num of charactes in a string *
* Params:                                             *
*        str - string to size its length              *
* return value: no of characters                      *
*           Excluding '\0' characters                 *
* Complexity:                                         *
* Time - O(n).                                        *
* Auxilary space - O(n)                               *
******************************************************/
size_t StrLen(const char *str);
/******************************************************
* Description: Compare two string                     *
* Params:                                             *
*        str1 - first string to compare to            *
*        str2 - second string to compare              *
* return value: in case equal string - 0              *
*			if str1 > str2 - integer bigger than 0    *
*           if str1 < str2 - integer bigger than 0    *
* Complexity:                                         *
* Time - O(n).                                        *
* Auxilary space - O(n)                               *
******************************************************/
int StrCmp( const char *str1, const char *str2);
/******************************************************
* Description: Copy src string to dest                *
* Params:                                             *
*        destination - The string to copy to          *
*        source - the string to copy from             *
* return value: a pointer to the resulting string dest*
*				the user destination string           *
*               must be capable to fill the src       *
* Complexity:                                         *
* Time - O(n).                                        *
* Auxilary space - O(n)                               *
******************************************************/
char *StrCpy(char *destination, const char *source);
/******************************************************
* Description: Concatenate Two Strings                *
* Params:                                             *
*        destination - The string to concat to        *
*        src - the string that being concated         *
* return value: a pointer to the resulting string dest*
*				the user destination string           *
*               must be capable to fill the src       *
* Complexity:                                         *
* Time - O(n).                                        *
* Auxilary space - O(n)                               *
******************************************************/
char *StrCat(char *destination, const char *src);
/*****************************************************
* Description: Find First occurence of needle in     *
*                                       haystack     *
* Params:                                            *
*        haystack - the string to search in          *
*        needle - the string to find in haystack     *
* return value: a ptr to the first occurence of      *
*              the needle in haystack                *
*				Upon failure: NULL                   *
* Complexity:                                        *
* Time - O(n^2).                                     *
* Auxilary space - O(n)                              *
*****************************************************/
char *StrStr(const char *haystack, const char *needle);
/*****************************************************
* Description: Sort A give Stack                     *
* Params:                                            *
*        stack - the stack to sort                   *
* return value: void                                 *
				sending invalid stack                *
				cause undefined behaviour            *
* Complexity:                                        *
* Time - O(n^2).                                     *
* Space - O(n)                                       *
*****************************************************/
void StackSort(stack_ty *stack);
#endif /* __ILRD_OL127_128_RECURSION_H__ */
