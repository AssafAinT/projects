/*****************************************************
 * Queue WS                                          *
 * Assaf Ainhoren                                    *
 * Reviewer: Ester Shpoker                           *
 * date: 05.06.2022                                  *
 *****************************************************/


/********************************libraries includes****************************/
#include <stdio.h> /*printf */
#include <assert.h> /* assert */

#include "queue.h"


/********************************Test Function*********************************/

int main(void)
{
	queue_ty *first_queue = QueueCreate();
	queue_ty *second_queue = QueueCreate();
	
	int x = 12;
	int y = 13;
	int z = 6;
	int second_q_data1 = 88;
	int second_q_data2 = 21212;
	int second_q_data3 = 77;
	size_t runner = 1;
	
	printf("%ld size\n", QueuetSize(first_queue));
	
	assert(1 == QueueIsEmpty(first_queue));
	assert(0 ==QueueEnqueue(first_queue, &x));
	assert(0 ==QueueEnqueue(first_queue, &y));
	assert(0 ==QueueEnqueue(first_queue, &z));
	
	assert(1 == QueueIsEmpty(second_queue));	
	assert(0 ==QueueEnqueue(second_queue, &second_q_data1));
	assert(0 ==QueueEnqueue(second_queue, &second_q_data2));
	assert(0 ==QueueEnqueue(second_queue, &second_q_data3));
	
	printf("first queue size %ld \n", QueuetSize(first_queue));
	
	printf("second queue size %ld \n", QueuetSize(first_queue)); 	
	
	QueueAppend(first_queue, second_queue);

	while (0 != QueuetSize(first_queue))
	{
		
		printf("slot no [%ld] : %d\n",runner, *(int *)QueuePeek(first_queue)); 
		QueueDequeue(first_queue);
		printf("%ld size\n", QueuetSize(first_queue));
		++runner;	
	}
	
	QueueDestroy(first_queue);
	
	return (0);
}

