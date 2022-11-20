/*****************************************************
 * Task                                              *
 * Assaf Ainhoren                                    *
 * Reviewer: Eitan Akrish                            *
 * date: 19.06.2022                                  *
 *****************************************************/
 


/********************************libraries includes****************************/

#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */
#include "task.h"
/********************************struct defintion******************************/
struct task
{
	uid_ty uid;
	size_t time_interval;
	time_t prior_time;
	task_func task;
	void *task_param;
	cleanup_task cleanup;
	void *cleanup_param;
};
/********************************funcs defintion******************************/
task_ty *CreateTask(task_func operation,
					void *task_param,
					cleanup_task cleanup,
					void *cleanup_param,
					size_t time_interval)
{
	task_ty *task  = malloc(sizeof(task_ty));
	if (NULL == task)
	{
	
		return NULL;
		
	}
	task->uid = UidCreate();
	if (UidIsEqual(task->uid , bad_uid))
	{
	
		free(task);
		return NULL;
	
	}
		task->time_interval = time_interval;
		task->prior_time = task->uid.time + time_interval;
		task->task = operation;
		task->task_param = task_param;
		task->cleanup = cleanup;
		task->cleanup_param = cleanup_param;
	return task;	
}

void DestroyTask(task_ty *task)
{
	free(task);
	task = NULL;
}

uid_ty GetUid(task_ty *task)
{
	return (task->uid);
}

task_func GetTask(task_ty *task)
{
	assert(NULL!= task);
	
	return (task->task);
}

int RunTask(task_ty *task)
{
	assert(NULL != task);

	return (task->task(task->task_param));
}

void RunClean(task_ty *task)
{
	assert(NULL != task);
	task->cleanup(task->cleanup_param);
}
void *GetTaskParam(task_ty *task)
{
	return(task->task_param);
}

size_t GetTaskTimeInterval(task_ty *task)
{
	return (task->time_interval);
}

void UpdateTaskRunTime(task_ty *task)
{
	time_t curr_time = 0;
	assert(NULL != task);
	curr_time = time(NULL);
	if (-1 == curr_time)
	{
		task->prior_time = -1;	
	}
	task->prior_time = curr_time + task->time_interval;
	
}


time_t GetTaskPriorTime(task_ty *task)
{
	return (task->prior_time);
}
void *GetCleanUpParam(task_ty *task)
{
	return (task->cleanup_param);
}

/*
task_func GetCleanUp(task_ty *task)
{
	assert(NULL!= task);
	
	return (task->cleanup);
}*/
