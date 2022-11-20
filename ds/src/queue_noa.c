#include <assert.h>		/* assert */
#include <stdlib.h> 	/* malloc, free */

#include "queue.h"
#include "slist.h"

struct queue
{
	slist_ty *slist;	
};


queue_ty *QueueCreate(void)
{
	queue_ty *queue = (queue_ty *)malloc(sizeof(queue_ty));
	if (NULL == queue)
	{
		return (NULL);
	}

	queue->slist = SlistCreate();
	if (NULL == queue->slist)
	{
		free (queue);
		return (NULL);
	}

	return (queue);
}


void QueueDestroy(queue_ty *queue)
{
	assert (NULL != queue);

	SlistDestroy(queue->slist);

	free(queue);
}


int QueueEnqueue(queue_ty *queue, void  *data)
{
	slist_iterator_ty rear = NULL;

	assert (NULL != queue);

	rear = SlistInsertBefore(SlistEnd(queue->slist), data);

	if (NULL == rear)
	{
		return (1);
	}

	return (0);
}


void QueueDequeue(queue_ty *queue)
{
	slist_iterator_ty front = NULL;

	assert (NULL != queue);

	front = SlistBegin(queue->slist);
	
	SlistRemove(front);
}


void *QueuePeek(const queue_ty *queue)
{
	assert (NULL != queue);	

	return (SlistGetData(SlistBegin(queue->slist)));
}


size_t QueuetSize(const queue_ty *queue)
{
	assert (NULL != queue);

	return (SlistSize(queue->slist));
}


int QueueIsEmpty(const queue_ty *queue)
{
	assert (NULL != queue);

	return (SlistIsEmpty(queue->slist));
}


void QueueAppend(queue_ty *dest, queue_ty *src)
{
	assert (NULL != dest);
	assert (NULL != src);

	SlistAppend(dest->slist, src->slist);
}

/*
void QueueDisplayQueue(const queue_ty *queue)
{
	assert (NULL != queue);

	SlistDisplayList(queue->slist);
}*/
