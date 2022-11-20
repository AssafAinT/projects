/*****************************************************
 * Task                                              *
 * Assaf Ainhoren                                    *
 * Reviewer:                                         *
 * date: 19.06.2022                                  *
 *****************************************************/
 


/********************************libraries includes****************************/

#include "uid.h"

/********************************typedefs**************************************/
typedef struct task task_ty; 
typedef int (*task_func)(void *task_param);
typedef void (*cleanup_task)(void *cleanup_param);

/***************************function declartions*******************************/

/*****************************************************
* Description: Creating Task                         *
* Return value: The Pointer to the Task struct.      *
*			upon failure : NULL                      *
* Complexity:                                        *
* Time - O(1).                                       *
* Space -O(n).                                       *
*****************************************************/

task_ty *CreateTask(task_func operation,
					void *task_param,
                    cleanup_task cleanup,
                    void *cleanup_param,
                    size_t time_interval);

/*****************************************************
* Description: Destroy task                          *
* Complexity:                                        *
* Time - O(1).                                       *
* Space -O(1).                                       *
*****************************************************/
void DestroyTask(task_ty *task);

/*****************************************************
* Description: Returning task UID                    *
* Return value: The UID of the task.                 *
*			upon failure : Bad UID                   *
* Complexity:                                        *
* Time - O(1).                                       *
* Space -O(1).                                       *
*****************************************************/
uid_ty GetUid(task_ty *task);
/*****************************************************
* Description: Returning task UID                    *
* Return value: a pointer to the function.           *
*			upon failure : NULL                      *
* Complexity:                                        *
* Time - O(1).                                       *
* Space -O(1).                                       *
*****************************************************/
task_func GetTask(task_ty *task);
/*****************************************************
* Description: Execute a given task                  *
* Return value: 1 upon success 0 otherwise.          *
* Complexity:                                        *
* Time - O(n).                                       *
* Space -O(1).                                       *
*****************************************************/
int RunTask(task_ty *task);
/*****************************************************
* Description: Execute a given cleanup task          *
* Return value: 1 upon success 0 otherwise.          *
* Complexity:                                        *
* Time - O(n).                                       *
* Space -O(1).                                       *
*****************************************************/
void RunClean(task_ty *task);
/*****************************************************
* Description: retriving the task param              *
* Return value: a pointer of the param               *
* Complexity:                                        *
* Time - O(1).                                       *
* Space -O(1).                                       *
*****************************************************/
void *GetTaskParam(task_ty *task);
/*****************************************************
* Description: retrive task time interval            *
* Return value: no of second of interval             *
* Complexity:                                        *
* Time - O(1).                                       *
* Space -O(1).                                       *
*****************************************************/

size_t GetTaskTimeInterval(task_ty *task);
/*****************************************************
* Description: update run time                       *
* Complexity:                                        *
* Time - O(1).                                       *
* Space -O(1).                                       *
*****************************************************/
void UpdateTaskRunTime(task_ty *task);
/*****************************************************
* Description: Get the task execute time             *
* Return value: the time in time_t display           *
* Complexity:                                        *
* Time - O(1).                                       *
* Space -O(1).                                       *
*****************************************************/
time_t GetTaskPriorTime(task_ty *task);
/*****************************************************
* Description: retriving the cleanup task param      *
* Return value: a pointer of the param               *
* Complexity:                                        *
* Time - O(1).                                       *
* Space -O(1).                                       *
*****************************************************/
void *GetCleanUpParam(task_ty *task);

/*task_func GetCleanUp(task_ty *task);
*/

