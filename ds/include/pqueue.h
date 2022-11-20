#ifndef __ILRD_OL127_128_PRIORITY_QUEUE_H__
#define __ILRD_OL127_128_PRIORITY_QUEUE_H__
/*****************************************************
 * Priority-Queue                                    *
 * Assaf Ainhoren                                    *
 * Reviewer: Eitan Akrish                            *
 * date: 22.06.2022                                  *
 *****************************************************/
 


/********************************libraries includes****************************/
#include <stddef.h> /* size_t */

/********************************typedefs**************************************/
typedef int (*cmp_priority_func)(void *data1, void *data2, void *params);
typedef int (*is_data_match_ty)(const void *data, void *params);
typedef struct pqueue pqueue_ty;

/***********************************function declarations**********************/

/*****************************************************
* Description: Creating Priority-Queue.              *
* Return value: a pointer to the new Priority-Queue. *
*			upon failure : NULL.                     *
* Complexity:                                        *
* Time - O(1).                                       *
* Space - O(1).                                      *
*****************************************************/
pqueue_ty *PQueueCreate(cmp_priority_func cmp_priority, void *param);

/*****************************************************
* Description: Destroying Priority-Queue.            *
* Complexity:                                        *
* Time - O(n).                                       *
* Space - O(1).                                      *
*****************************************************/
void PQueueDestroy(pqueue_ty *pqueue); 
/*****************************************************
* Description: Inserting a data and sorting by       *
* priority                                           *
* Return value: 0 if insertion successed.            *
*			upon failure : 1.                        *
* Complexity:                                        *
* Time - O(n).                                       *
* Space - O(1).                                      *
*****************************************************/
int PQueueEnqueue(pqueue_ty *pqueue, void *data);
/*****************************************************
* Description: Removing a data from the queue        *
* Complexity:                                        *
* Time - O(1).                                       *
* Space - O(1).                                      *
*****************************************************/
void PQueueDequeue(pqueue_ty *pqueue); 
/*****************************************************
* Description:Retriving the data from the top element*
* Return value: a pointer to the data                *
*			upon failure : NULL.                     *
* Complexity:                                        *
* Time - O(1).                                       *
* Space - O(1).                                      *
*****************************************************/
void *PQueuePeek(const pqueue_ty *pqueue);
/*****************************************************
* Description:Computing the size of the queue        *
* Return value: Number of elements in the queue      *
* Complexity:                                        *
* Time - O(1).                                       *
* Space - O(1).                                      *
*****************************************************/
size_t PQueueSize(const pqueue_ty *pqueue);
/*****************************************************
* Description:Computing if the queue is empty        *
* Return value: 1 if empty, otherwise 0              *
* Complexity:                                        *
* Time - O(1).                                       *
* Space - O(1).                                      *
*****************************************************/
int PQueueIsEmpty(const pqueue_ty *pqueue);
/*****************************************************
* Description:Clears the Queue from elements         *
* Complexity:                                        *
* Time - O(n).                                       *
* Space - O(1).                                      *
*****************************************************/
void PQueueClear(pqueue_ty *pqueue);
/*****************************************************
* Description:Erasing a specified element from queue *
* Return value: a pointer to the data that was erased*
*			upon failure : NULL.                     *
* Complexity:                                        *
* Time - O(n).                                       *
* Space - O(1).                                      *
*****************************************************/
void *PQueueErase(pqueue_ty *pqueue, is_data_match_ty is_match, void *param);

#endif /* __ILRD_OL127_128_PRIORITY_QUEUE_H__ */ 
