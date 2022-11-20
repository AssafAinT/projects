/*****************************************************
 * Priority-Queue                                    *
 * Assaf Ainhoren                                    *
 * Reviewer: Eitan Akrish                            *
 * date: 22.06.2022                                  *
 *****************************************************/
 


/********************************libraries includes****************************/
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */

#include "pqueue.h"
#include "srtlist.h" 


struct pqueue
{
    srtlist_ty *queue;
    size_t size;
};

pqueue_ty *PQueueCreate(cmp_priority_func cmp_priority, void *param)
{
	pqueue_ty *prior_queue = (pqueue_ty *)malloc(sizeof(pqueue_ty));
	if (NULL == prior_queue)
	{
		return (NULL);
	}
	
	prior_queue->queue = SrtlistCreate(cmp_priority, param);
	if (NULL == prior_queue->queue)
	{
		free(prior_queue);
		prior_queue = NULL;
		return (NULL);
	}
	prior_queue->size = 0;
	return (prior_queue);
}

void PQueueDestroy(pqueue_ty *pqueue)
{
	assert (NULL != pqueue);
	
	SrtlistDestroy(pqueue->queue);
	free(pqueue);
	pqueue = NULL;
}

int PQueueEnqueue(pqueue_ty *pqueue, void *data)
{
	int ret_stat = 0;
	
	assert (NULL != pqueue);
	
	if (SrtlistIterIsEqual((SrtlistEnd(pqueue->queue)),
	                      (SrtlistInsert(pqueue->queue, data))))
	{
		ret_stat = 1;
	}
	else
	{
		++pqueue->size;
	}
	return (ret_stat);
}

void PQueueDequeue(pqueue_ty *pqueue)
{
	assert (NULL != pqueue);
	
	SrtlistRemove(SrtlistBegin(pqueue->queue));
	--pqueue->size;
} 

void *PQueuePeek(const pqueue_ty *pqueue)
{
	assert (NULL != pqueue);
	
	return (SrtlistGetData(SrtlistBegin(pqueue->queue)));
}

size_t PQueueSize(const pqueue_ty *pqueue)
{
	assert (NULL != pqueue);
	
	return (pqueue->size);
}

int PQueueIsEmpty(const pqueue_ty *pqueue)
{
	assert (NULL != pqueue);
	return (SrtlistIsEmpty(pqueue->queue));
}

void PQueueClear(pqueue_ty *pqueue)
{
	assert (NULL != pqueue);
		
	while (!PQueueIsEmpty(pqueue))
	{
		PQueueDequeue(pqueue);
	}
	

}

void *PQueueErase(pqueue_ty *pqueue, is_data_match_ty is_match, void *param)
{
	srtlist_iterator_ty found ={0};
	void *data = NULL;
	
	assert(NULL != pqueue);
	assert(NULL != pqueue->queue);
	assert(NULL != is_match);

	found = SrtlistFindIf(SrtlistBegin(pqueue->queue),
				          SrtlistEnd(pqueue->queue),
				          is_match,
				          param);
				          
	if (SrtlistIterIsEqual(found, SrtlistEnd(pqueue->queue)))
	{
		return (NULL);
	}
	data = SrtlistGetData(found);
	SrtlistRemove(found);
	--pqueue->size;
	return (data);

}
