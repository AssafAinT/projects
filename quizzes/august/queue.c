/*****************************************************
 * Queue WS                                          *
 * Assaf Ainhoren                                    *
 * Reviewer: Ester Shpoker                           *
 * date: 05.06.2022                                  *
 *****************************************************/
 
/************************************Macros Definition*************************/
#define SUCCESS 0
#define FAIL 1
/********************************libraries includes****************************/
#include <stddef.h> /* size_t */ 
#include <stdlib.h> /*malloc, free */
#include <assert.h> /*assert */

#include "slist.h" /* slist function */
#include "queue.h"

/*******************************Struct Definition******************************/
struct queue 
{
	slist_ty *slist;
};
/*******************************Function Definition****************************/
queue_ty *QueueCreate(void)
{
	queue_ty *new_queue = (queue_ty *)malloc(sizeof(queue_ty));
	if (NULL == new_queue)
	{
		return (NULL);
	}
	
	new_queue -> slist = SlistCreate();	
	if (NULL == new_queue->slist)
	{
		return (NULL);
	}
	return (new_queue);
}

void QueueDestroy(queue_ty *queue)
{
	assert(NULL != queue);
	assert(NULL != queue->slist);
	
	SlistDestroy(queue->slist);
	
	free(queue);
	queue = NULL;
} 

int QueueEnqueue(queue_ty *queue, void  *data)
{
	int result = SUCCESS;
	
	assert(NULL != queue);
	assert(NULL != queue->slist);
	
	if (NULL == SlistInsertBefore(SlistEnd(queue->slist), data))
	{
		result = FAIL;
	}
	
	return (result);
}

void QueueDequeue(queue_ty *queue)
{
	assert(NULL != queue);
	assert(NULL != queue->slist);
	
	SlistRemove(SlistBegin(queue->slist));
}
void *QueuePeek(const queue_ty *queue)
{
	assert(NULL != queue);
	assert(NULL != (queue->slist));
	
	
	return (SlistGetData(SlistBegin(queue -> slist)));
}

size_t QueuetSize(const queue_ty *queue)
{
	assert(NULL != queue);
	assert(NULL != queue->slist);
	
	return (SlistSize(queue->slist));
}

int QueueIsEmpty(const queue_ty *queue)
{
	return (SlistIsEmpty(queue->slist));
}

void QueueAppend(queue_ty *dest, queue_ty *src)
{
	assert(NULL != dest);
	assert(NULL != src);
	assert(NULL != dest->slist);
	assert(NULL != src->slist);
	
	SlistAppend(dest->slist , src->slist);
	
	free(src);
}


