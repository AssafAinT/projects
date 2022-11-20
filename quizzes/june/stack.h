/*****************************************************
 * WS11                                              *
 * Assaf Ainhoren                                    *
 * Reviewer: Ester Shpoker                           *
 * date: 05.06.2022                                  *
 *****************************************************/
 
#ifndef __ILRD_OL127_128__STACK_H__ /* header_guard */
#define __ILRD_OL127_128__STACK_H__

#include <stddef.h> /* size_t */

typedef struct stack stack_ty;

/* Function that cretes the stack according to user amount of elements and 
the size_of_elements. the function returns a pointer to the allocated stack
time_complexity O(1) */
stack_ty *StackCreate(size_t element_amount, size_t size_of_element);

/* Function that destroies the specified stack.
time_complexity O(1) */
void StackDestroy(stack_ty *stack);

/* The function pops the last element of the stack (LIFO) and the stack point to
the element above. time_complexity O(1) 
exceptions: the function could fail if the stack is empty.*/
void StackPop(stack_ty *stack);
/* The function push a new element to the stack (LIFO) the top of the stack now
points to the new element. time_complexity O(1) 
exceptions: the function could fail if the stack is full.*/
void StackPush(stack_ty *stack, const void *element);

/* The function reads the last element of the stack (LIFO).
Returns the a pointer to the top element of the stack. 
time_complexity O(1) 
exceptions: the function could fail if the stack is empty.*/
void *StackPeek(const stack_ty *stack);
/* The function Returns the current size of to the stack. 
time_complexity O(1) */
size_t StackSize(const stack_ty *stack);
/* the function returns True if the stack is empty, else false */
int StackIsEmpty(const stack_ty *stack);
/* returns the total size(in bytes) of the stack 
time complexity O(1).*/
size_t StackCapacity(const stack_ty *stack);


#endif /* __ILRD_OL127_128_STACK_H__ */
