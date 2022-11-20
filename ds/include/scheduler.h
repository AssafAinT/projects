#ifndef __ILRD_OL127_128_SCHEDULER_H__
#define __ILRD_OL127_128_SCHEDULER_H__
/*****************************************************
 * Scheduler                                         *
 * Assaf Ainhoren                                    *
 * Reviewer: Eitan Akrish                            *
 * date: 19.06.2022                                  *
 *****************************************************/
 


/********************************libraries includes****************************/
#include <stddef.h> /* size_t */
#include "uid.h"

typedef int (*operation_func)(void *task_param);
typedef void (*cleanup_func)(void *cleanup_param);
typedef struct scheduler scheduler_ty;
/***************************function declartions*******************************/

/*****************************************************
* Description: Creating Scheduler                    *
* Return value: The Pointer to the Task struct.      *
*			upon failure : NULL                      *
* Complexity:                                        *
* Time - O(1).                                       *
* Space -O(n).                                       *
*****************************************************/
scheduler_ty *SchedulerCreate(void);
/*****************************************************
* Description: Destroy Scheduler                     *
* Complexity:                                        *
* Time - O(1).                                       *
* Space -O(1).                                       *
*****************************************************/
void SchedulerDestroy(scheduler_ty *scheduler); 
/*****************************************************
* Description: Adding task to the scheduler          *
* Return value: valid uid                            *
*			upon failure : Bad Uid                   *
* Complexity:                                        *
* Time - O(n).                                       *
* Space -O(n).                                       *
*****************************************************/
uid_ty SchedulerAddTask(scheduler_ty *scheduler,
						operation_func task,
                        void *task_param, cleanup_func cleanup,
                        void *cleanup_param, size_t time_interval);
/*****************************************************
* Description: Removing task                         *
* Return value: 0 for succes                         *
*			upon failure : 1                         *
* Complexity:                                        *
* Time - O(n).                                       *
* Space -O(1).                                       *
*****************************************************/
int SchedulerRemoveTask(scheduler_ty *scheduler, uid_ty uid); 
/*****************************************************
* Description: Executing task                        *
* Return value: 0                                    *
*			upon failure : interget other than 0     *
* Complexity:                                        *
* AmortisedTime - O(n).                              *
* Space -O(n).                                       *
*****************************************************/
int SchedulerRun(scheduler_ty *scheduler); 
/*****************************************************
* Description: stoping  a task to the scheduler      *
* Complexity:                                        *
* Time - O(n).                                       *
* Space -O(n).                                       *
*****************************************************/
void SchedulerStop(scheduler_ty *scheduler);
/*****************************************************
* Description: size of scheduler                     *
* Return value: the amount of tasks in scheduler     *
* Complexity:                                        *
* Time - O(1).                                       *
* Space -O(1).                                       *
*****************************************************/
size_t SchedulerSize(const scheduler_ty *scheduler);
/*****************************************************
* Description: checking if scheduler empty           *
* Return value: 1 for succes                         *
*			upon failure : 0                         *
* Complexity:                                        *
* Time - O(n).                                       *
* Space -O(1).                                       *
*****************************************************/
int SchedulerIsEmpty(const scheduler_ty *scheduler);
/*****************************************************
* Description: Clearing the scheduler from tasks     *
* Complexity:                                        *
* Time - O(n).                                       *
* Space -O(1).                                       *
*****************************************************/
void SchedulerClear(scheduler_ty *scheduler);

#endif /* __ILRD_OL127_128_SCHEDULER_H__ */ 
