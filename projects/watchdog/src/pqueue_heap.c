/*****************************************************
 * Priority-Queue                                    *
 * Assaf Ainhoren                                    *
 * Reviewer: Eitan Akrish                            *
 * date: 22.06.2022                                  *
 *****************************************************/

/********************************libraries includes****************************/
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */

#include "pqueue_heap.h"
#include "heap.h" 


struct pqueue
{
    heap_ty *pqueue;
};

pqueue_ty *PQueueCreate(cmp_func cmp_priority, void *param)
{
	pqueue_ty *prior_queue = (pqueue_ty *)malloc(sizeof(pqueue_ty));
	if (NULL == prior_queue)
	{
		return (NULL);
	}
	
	prior_queue->pqueue = HeapCreate(cmp_priority, param);
	if (NULL == prior_queue->pqueue)
	{
		free(prior_queue);
		prior_queue = NULL;
		return (NULL);
	}
	return (prior_queue);
}

void PQueueDestroy(pqueue_ty *pqueue)
{
	assert (NULL != pqueue);
	
	HeapDestroy(pqueue->pqueue);
	free(pqueue);
	pqueue = NULL;
}

int PQueueEnqueue(pqueue_ty *pqueue, void *data)
{
	assert (NULL != pqueue);
	
	return (HeapPush(pqueue->pqueue, data));
}

void PQueueDequeue(pqueue_ty *pqueue)
{
	assert (NULL != pqueue);
	
    HeapPop(pqueue->pqueue);

} 

void *PQueuePeek(const pqueue_ty *pqueue)
{
	assert (NULL != pqueue);
	
	return (HeapPeek(pqueue->pqueue));
}

size_t PQueueSize(const pqueue_ty *pqueue)
{
	assert (NULL != pqueue);
	
	return (HeapSize(pqueue->pqueue));
}

int PQueueIsEmpty(const pqueue_ty *pqueue)
{
	assert (NULL != pqueue);
	return (HeapIsEmpty(pqueue->pqueue));
}

void PQueueClear(pqueue_ty *pqueue)
{
	assert (NULL != pqueue);
		
	while (!PQueueIsEmpty(pqueue))
	{
		PQueueDequeue(pqueue);
	}	
}

void *PQueueErase(pqueue_ty *pqueue, is_match_func is_match, void *param)
{
	assert(NULL != pqueue);
	assert(NULL != pqueue->pqueue);
	assert(NULL != is_match);
	
	return(HeapRemove(pqueue->pqueue, param,is_match));
}
