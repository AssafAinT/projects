/****************************************************
* Watchdog                                          *
* Assaf Ainhoren                                    *
* Reviewer: Haggai Newman                           *
* date: 31.08.2022                                  *
****************************************************/
/********************************libraries includes****************************/
#define _POSIX_C_SOURCE 200112L /*setenv*/
#define _XOPEN_SOURCE 500 /*realpath*/

#include <pthread.h> /* mutex_function */
#include <stdlib.h> /* getenv, setenv, atoi, realpath*/
#include <fcntl.h> /* For O_* constants */
#include <sys/stat.h>  /* For mode constants*/
#include <semaphore.h> /* semaphore system calls */
#include <signal.h> /* signals */
#include <string.h> /* memset */
#include <assert.h> /* assert */
#include <unistd.h> /* fork, exec, sleep, getpid */
#include <sys/wait.h> /* wait */
#include <stdatomic.h> /* atomic function */

#include <stdio.h> /* sprintf ,tests printf, perror */



#include "watchdog.h" /* watchdog.h */
#include "scheduler_heap.h" /* scheduler_heap */

#define INT_MAX_DIGITS 10
#define WD_PID_MAX_LENGTH 19
#define MAX_ENV 200
#define MAX_PATH 4096
#define MAX_SEM_NAME 254
#define IGNORE_DOT_SLASH 2
#define UNUSED(param)  (void)param


static sem_t *g_ipc_semaphore = NULL;
static sem_t *g_watch_dog_build_sem =NULL;
static char g_sem_name[MAX_SEM_NAME] = {'\0'};
static char g_wd_sem[MAX_SEM_NAME] = {'\0'};
/*static const char *g_sem_name = "watchdog";
static const char *g_wd_sem = "build";*/
static atomic_size_t thread_counter = 0;
static struct sigaction sa;
static struct sigaction sa2;
static pid_t watchd_pid = 0;
static scheduler_ty *scheduler = NULL;
static pthread_attr_t attr;
static wd_status_ty g_wd_error = SUCCESSED;
static size_t g_base_ten = 10;
static size_t g_biggest_mudulo_ten_remainder = 9;
static size_t g_zero_character = 48;
static size_t g_ascii_of_a = 97;

static status_ty RunPreSettings(char *executable_name);
static status_ty CreateClientThread(void);
static status_ty SemaphoreConfigurations(char *executable_name);
static status_ty SetSignals(void);

static void SetThreadParams(size_t time_interval,
                           size_t threshold,
                           const char *executable_name);
static void *CommunicationThread(void *args);
static status_ty CreateWatchDog( const char *executable_name);
static void SetWdPid(pid_t wd_pid);

void WdSaysHello(int sig, siginfo_t *info, void *data);
void WdIsInTrouble(int sig, siginfo_t *info, void *data);
int KnockKnockWd(void *task_param);

static int StopThreadScheduler(void *param);
static void StopThreadSchedulerCleanUp(void *param);

static status_ty GeneralErrorHandling(const char *error);
static void *ThreadErrorHandling(const char *error);

static char *ItoA(int num, char *buffer);
void ReverseStr(char *start, char *end);

typedef struct thread
{
	size_t threshold;
	size_t time_interval;
	const char *executable_name;
	pid_t caller_pid;
}thread_ty;
thread_ty thread_params = {0};

wd_status_ty MakeMeImmortal(size_t time_interval,
                         size_t threshold,
                         char *executable_name)
{	
	SetThreadParams(time_interval, threshold,executable_name);
	
	if (SUCCESSED != (wd_status_ty)RunPreSettings(executable_name))
	{
		return FAILED;
	}
	if (SUCCESSED != (wd_status_ty)CreateClientThread())
	{
		return FAILED;
	}		

	if (NULL == getenv("WD_PID"))
	{
		setenv("WD_PID", "0", 1);
		if (FAIL ==  CreateWatchDog(executable_name))
		{
			g_wd_error = CREATE_WD_FAIL;
			return ((wd_status_ty) GeneralErrorHandling("create WD failed"));
		}
	}
	else
	{
#ifndef NDEBUG
		write(1, "here after revive\n", 19);
#endif
		watchd_pid = atoi(getenv("WD_PID"));
		sem_post(g_ipc_semaphore);
	}
	
	sem_wait(g_watch_dog_build_sem);
	
	return g_wd_error;
}

static status_ty GeneralErrorHandling(const char* error)
{
#ifndef NDEBUG
	perror(error);
#endif
	return FAIL;
}
void LetMeDie(void)
{
	SchedulerAddTask(scheduler, StopThreadScheduler,NULL,
                         StopThreadSchedulerCleanUp ,NULL, 0);
	
	kill(watchd_pid, SIGUSR2);
	pause();
	
	unsetenv("WD_PID");
	pthread_attr_destroy(&attr);
	
	sem_unlink(g_sem_name);
	sem_unlink(g_wd_sem);
	sem_close(g_ipc_semaphore);
    sem_close(g_watch_dog_build_sem);
	
	SchedulerDestroy(scheduler);
}

static int StopThreadScheduler(void *param)
{
	UNUSED(param);
    SchedulerStop(scheduler);

    return (FAIL);
}
static void StopThreadSchedulerCleanUp(void *param)
{
	UNUSED(param);
	SchedulerClear(scheduler);
}

static void *CommunicationThread(void *args)
{
	thread_ty *params = (thread_ty *)args;
	uid_ty thread_task = {0};
	
	scheduler =  SchedulerCreate();
	if (NULL == scheduler)
	{
		g_wd_error = SCHEDULER_CREATE_ERROR;
		return (ThreadErrorHandling("scheduler not created"));
	}
	
	thread_task = SchedulerAddTask(scheduler, KnockKnockWd,
	                              (void *)params->threshold,
	                              NULL, NULL, params->time_interval);
	if (UidIsEqual(thread_task, bad_uid))
	{
		SchedulerDestroy(scheduler);
		g_wd_error = BAD_UID;
		return (ThreadErrorHandling("bad uid found"));
	}
	sem_wait(g_ipc_semaphore);
	SchedulerRun(scheduler);
	
	return (NULL);
}
static void *ThreadErrorHandling(const char *error)
{
#ifndef NDEBUG
	perror(error);
#endif
	return NULL;
}
int KnockKnockWd(void *task_param)
{
	size_t threshold = (size_t )task_param;
	atomic_fetch_add(&thread_counter, 1);

	if (thread_counter <= threshold)
	{
#ifndef NDEBUG
		write(1, "client: pong\n", 14);
#endif
		kill(watchd_pid, SIGUSR1);
	}
	else if (thread_counter >= threshold)
	{
#ifndef NDEBUG
		write(1, "reviving watchdog\n", 19);
#endif
		waitpid(watchd_pid, NULL,WNOHANG);
		unsetenv("WD_PID");

		if (FAIL == CreateWatchDog(thread_params.executable_name))
		{
			return FAIL;
		}
		sem_wait(g_ipc_semaphore);
		atomic_fetch_sub(&thread_counter, thread_counter);
	}

	return SUCCESS;
}

void WdSaysHello(int sig, siginfo_t *info, void *data)
{
	UNUSED(data);
    UNUSED(info);
    if (sig == SIGUSR1)
    {
        atomic_fetch_sub(&thread_counter, thread_counter);
    }   
}

void WdIsInTrouble(int sig, siginfo_t *info, void *data)
{
	UNUSED(data);
    UNUSED(info);
    if (sig == SIGUSR2)
    {
		sem_post(g_watch_dog_build_sem);
   	 	sem_post(g_ipc_semaphore);
		SchedulerStop(scheduler);
		g_wd_error = WD_CREATE_FAIL;
    }   
}
static status_ty SetSignals(void)
{
	memset(&sa, 0, sizeof(sa));
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = WdSaysHello;
    if (0 != sigaction(SIGUSR1, &sa, NULL))
	{
		return FAIL;
	}
	memset(&sa2, 0, sizeof(sa2));
    sa2.sa_flags = SA_SIGINFO;
    sa2.sa_sigaction = WdIsInTrouble;
    if (0 != sigaction(SIGUSR2, &sa2, NULL))
	{
		return FAIL;
	}
	return SUCCESS;
}

static status_ty CreateWatchDog(const char *executable_name)
{
	pid_t wd_pid = fork();
	int ret_value = 0;
	char time_inter_char[INT_MAX_DIGITS] = "";
	char threshold_char[INT_MAX_DIGITS] = "";
	char caller_char[INT_MAX_DIGITS] = "";
	char realpath_buffer[MAX_PATH] = "";

	if (0 > wd_pid)
	{
		g_wd_error = FORK_FAIL;
		return FAIL; 
	}    
	if (0 == wd_pid)
	{
		char *argv[9] = {""};
		argv[0] = "watchdog_process";
		sprintf(time_inter_char, "%ld", thread_params.time_interval);
		argv[1] = time_inter_char;
		sprintf(threshold_char, "%ld", thread_params.time_interval);
		argv[2] = threshold_char;
		sprintf(caller_char, "%d", thread_params.caller_pid);
		argv[3]	= caller_char;
		if (NULL == realpath(executable_name,realpath_buffer))
		{
			return FAIL;
		}
		argv[4]	= realpath_buffer; 
		argv[5] = (char *)executable_name;
		argv[6] = g_sem_name;
		argv[7] = g_wd_sem;
		argv[8]	= NULL;

		ret_value = execv(realpath_buffer, argv);
		if (0 > ret_value)
		{
			g_wd_error = EXEC_FAIL;
#ifndef NDEBUG
			perror("execv abort");
#endif
			abort();
		}
	}
	else
	{
		watchd_pid = wd_pid;
		SetWdPid(wd_pid);
	}

	return SUCCESS;
}

static void SetWdPid(pid_t wd_pid)
{
	char pid[INT_MAX_DIGITS] = "";
	ItoA(wd_pid, pid);
	setenv("WD_PID", pid, 1);
}


static void SetThreadParams(size_t time_interval,
                           size_t threshold,
                           const char *executable_name)
{
	thread_params.caller_pid = getpid();
	thread_params.threshold = threshold;
	thread_params.time_interval = time_interval;
	thread_params.executable_name = executable_name;
}

static status_ty SemaphoreConfigurations(char *executable_name)
{
	int value = 0;
	
	if (NULL != strcpy(g_sem_name, executable_name + IGNORE_DOT_SLASH))
	{
		strcat(g_sem_name, "_sem");
		printf("%s\n", g_sem_name);
		sem_unlink(g_sem_name);
		g_ipc_semaphore = sem_open(g_sem_name, O_CREAT , 0644, value);
		if (g_ipc_semaphore == SEM_FAILED)
		{
			return (GeneralErrorHandling("sem_open"));
		}
	}
	
	if (NULL != strcpy(g_wd_sem, executable_name + IGNORE_DOT_SLASH))
	{
		strcat(g_wd_sem, "_wd_build");
		sem_unlink(g_wd_sem);
		g_watch_dog_build_sem = sem_open(g_wd_sem, O_CREAT , 0644, value);
		if (g_watch_dog_build_sem == SEM_FAILED)
		{
			return (GeneralErrorHandling("sem_open"));
		}
	}
	
	return SUCCESS;
}
static status_ty RunPreSettings(char *executable_name)
{

	if(SUCCESS != SemaphoreConfigurations(executable_name))
	{
		return FAIL;	
	}
	
	if (SUCCESS != SetSignals())
	{
		return (GeneralErrorHandling("SetSignals failed"));
	}
	pthread_attr_init(&attr);
	
	if (SUCCESS != pthread_attr_setdetachstate(&attr , PTHREAD_CREATE_DETACHED))
	{
		return (GeneralErrorHandling("pthread_attr_setdetachstate failed"));
	}
	return SUCCESS;
}
static status_ty CreateClientThread(void)
{
	pthread_t comm_thread = 0;

	if (SUCCESS != pthread_create(&comm_thread, &attr,
								CommunicationThread, &thread_params))
	{
		g_wd_error = CREATE_THREAD_FAIL;
		return (GeneralErrorHandling("pthread_create failed"));
	}
	return SUCCESS;
}

static char *ItoA(int num, char *buffer)
{
	int remainder_of_num = 0;
	char *copy_of_buffer = buffer;
	char *end_of_buffer = buffer;
	
	if (0 == num)
	{
		*buffer = '0';
		++buffer;
		*buffer = '\0';
		return (--buffer);
	}

	while (num)
	{
		remainder_of_num = num % g_base_ten;
		if (g_biggest_mudulo_ten_remainder < remainder_of_num)
		{
			*end_of_buffer = (remainder_of_num - 10) + g_ascii_of_a;
		}
		else
		{
			*end_of_buffer = (remainder_of_num + g_zero_character);
		}
		num /= g_base_ten;
		++end_of_buffer;
	}
	--end_of_buffer;
	
	ReverseStr(copy_of_buffer, end_of_buffer);
	
	return (buffer);
}	
void ReverseStr(char *start_of_string, char *end_of_string)
{
	char copy_of_string = '\0';
	
	assert( NULL != start_of_string); 
	assert( NULL != end_of_string);
	
	while ( start_of_string < end_of_string )
	{
		copy_of_string = *start_of_string;
		*start_of_string = *end_of_string;
		*end_of_string = copy_of_string;
		
		--end_of_string;
		++start_of_string;
	}
}
