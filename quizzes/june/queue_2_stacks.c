#include <stdlib.h>   /* malloc, free */
#include <assert.h>   /* assert */
#include <stdlib.h>
#include <stdio.h>

#include "stack.h"


typedef struct queue2stack
{
	stack_ty *stack1;
	stack_ty *stack2;
}qtwos2_ty;

qtwos2_ty *Create(size_t size, size_t element_size)
{
	qtwos2_ty *queue = (qtwos2_ty *)malloc(sizeof(qtwos2_ty));
	if (NULL == queue)
	{
		return (NULL);
	}

	queue->stack1 = StackCreate(size, element_size);
	if (NULL == queue->stack1)
	{
		free(queue);
		return (NULL);
	}

	queue->stack2 = StackCreate(size, element_size);
	if (NULL == queue->stack2)
	{
		free(queue->stack1);
		free(queue);
		return (NULL);
	}

	return (queue);
}

void QueDestroy(qtwos2_ty *queue)
{
	StackDestroy(queue->stack1);
	StackDestroy(queue->stack2);
	free(queue);
}
void EnQueue(qtwos2_ty *queue, void *data)
{
	assert(NULL != queue);
	
	while (1 != StackIsEmpty(queue->stack1))
	{
		StackPush(queue->stack2, StackPeek(queue->stack1));
		StackPop(queue->stack1);
	}

	StackPush(queue->stack1, data);

	while (1 != StackIsEmpty(queue->stack2))
	{
		StackPush(queue->stack1, StackPeek(queue->stack2));
		StackPop(queue->stack2);
	}
}

void *QuePeek(qtwos2_ty *queue)
{
	
	return (StackPeek(queue->stack2));
}
void DeQueue(qtwos2_ty *queue)
{
	assert(NULL != queue);
	
	StackPop(queue->stack1);
}

int QueIsEmpty(qtwos2_ty *queue)
{
	assert(NULL != queue);
	assert(NULL != queue->stack1);
	assert(NULL != queue->stack2);
	
	return (StackIsEmpty(queue->stack1) || StackIsEmpty(queue->stack2));
}


int main(void)
{
	int num1 = 1;
	int num2 = 2;
	int num3 = 3;
	int num4 = 4;
	int num5 = 5;
	int num6 = 6;
	

	qtwos2_ty *queue = Create(6, 4);
	
	
	EnQueue(queue, &num1);
	EnQueue(queue, &num2);
	EnQueue(queue, &num3);
	EnQueue(queue, &num4);
	EnQueue(queue, &num5);
	EnQueue(queue, &num6);
	
	DeQueue(queue);
	
	printf("%d\n", *(int *)QuePeek(queue));


	QueDestroy(queue);
	
	return 0;
}


