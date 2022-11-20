/*****************************************************
 * Queue WS                                          *
 * Assaf Ainhoren                                    *
 * Reviewer: Ester Shpoker                           *
 * date: 05.06.2022                                  *
 *****************************************************/

#ifndef __ILRD_OL127_128_QUEUE_H__ /* header - guard */
#define __ILRD_OL127_128_QUEUE_H__


/********************************libraries includes****************************/
#include <stddef.h> /* size_t */


typedef struct queue queue_ty;

/********************************Function Declarations*************************/

/* Disclaimer: in all of the given function that requires the pointer of queue 
as a out param, Sending in invalid queue would result an undefined behavior */

/* Description: Creating Queue. 
Return value: a pointer to the new created queue.
			upon failure : NULL.
Complexity:
Time - O(1).
Space -O(n).*/
queue_ty *QueueCreate(void);

/* Description: Destroying the given queue.
ERROR: passing in invalid pointer causes an undefined behavior.
Complexity:
Time - O(n).
Space -O(1).*/
void QueueDestroy(queue_ty *queue); 

/* Description: Inserting data to the given queue.
Return value: 0 for success otherwise 1. 
	        ERROR: passing in invalid pointer causes an undefined behavior.
Complexity:
Time - O(1).
Space -O(1).*/
int QueueEnqueue(queue_ty *queue, void  *data);

/* Description: popping data from to the given queue.
ERROR: passing in invalid pointer causes an undefined behavior.
Complexity:
Time - O(1).
Space -O(1).*/
void QueueDequeue(queue_ty *queue);

/* Description: returns the data from to top of the queue.
ERROR: passing in invalid pointer causes an undefined behavior.
Complexity:
Time - O(n).
Space -O(1).*/
void *QueuePeek(const queue_ty *queue);

/* Description: returns the current size of the queue(no. of elements).
ERROR: passing in invalid pointer causes an undefined behavior.
Complexity:
Time - O(1).
Space -O(1).*/
size_t QueuetSize(const queue_ty *queue);

/*Description: compute for emptiness of the queue.

return value: 1 if empty, otherwise 0.
ERROR: passing in invalid pointer causes an undefined behavior.
Complexity:
Time - O(n).
Space -O(1).*/
int QueueIsEmpty(const queue_ty *queue);

/*Description: append the given src queue to the dest queue.
The function handles with releasing the dest memory.
ERROR: passing in invalid pointer causes an undefined behavior.

COMPLEXITY:
 time: O(1)
 space: O(n)
*/
void QueueAppend(queue_ty *dest, queue_ty *src);


#endif /* __ILRD_OL127_128_QUEUE_H__ */
