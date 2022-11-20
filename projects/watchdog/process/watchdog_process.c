/****************************************************
* Watchdog                                          *
* Assaf Ainhoren                                    *
* Reviewer: Haggai Newman                           *
* date: 31.08.2022                                  *
****************************************************/
/********************************libraries includes****************************/
#include <assert.h> /* assert */
#include <semaphore.h> /* sem_t */
#include <pthread.h> /* pthread_create, destroy, join */
#include <unistd.h> /* exec family, fork */
#include <sys/types.h> /* pid_t */
#include <fcntl.h> /* For O_* constants */
#include <sys/wait.h> /* wait */
#include <sys/syscall.h> /* Definition of SYS_* constants */
#include <signal.h> /* sig_action */
#include <stdlib.h> /* getenv, setenv */
#include <string.h> /* memset */
#include "watchdog.h" /* watchdog.h */
#include "scheduler_heap.h" /* scheduler_heap */
#include <stdio.h> /* debugging printf */

#define UNUSED(x) (void)x
#define MAX_CHAR 256
#define MAX_DIGITS 10

static sem_t *g_ipc_semaphore = NULL;
static sem_t *g_watch_dog_build_sem =NULL;
static atomic_size_t g_watchdog_counter = 0;
static struct sigaction sa;
static struct sigaction sa2;
static size_t time_interval =0;
static size_t threshold =0;
static pid_t pid_to_kill = 0;
static char executable[MAX_CHAR] = {'\0'};
static char name_of_process[MAX_CHAR] = {'\0'};
static char wd_pid_buff[MAX_DIGITS] = {'\0'};
static scheduler_ty *scheduler_wd = NULL;
static wd_status_ty g_wd_p_error = SUCCESSED;

void WatchDog(int sig, siginfo_t *info, void *data);
void StopTheParty(int sig, siginfo_t *info, void *data);
static status_ty SetSignals(void);
int WatchDogPong(void *task_param);
static int StopTheTrain(void *param);
static void StopTheTrainCleanUp(void *param);
static status_ty SemaphoreConfigurations(const char *g_sem_name, const char *g_wd_sem);
static status_ty SetEnv(void);
static status_ty SetArgv(char *argv[]);

int main(int argc, char *argv[], char *envp[])
{
    uid_ty wd_task = {0};
    
    if (SUCCESS != SemaphoreConfigurations(argv[6], argv[7]))
    {
#ifndef NDEBUG
        write(1, "Error: SemaphoreConfigurations failed\n", 39);
#endif
        kill(pid_to_kill, SIGUSR2);
        return g_wd_p_error;
    }

    if (SUCCESS != SetEnv())
    {
#ifndef NDEBUG
        write(1, "Error: SetEnv failed\n", 22);
#endif
        kill(pid_to_kill, SIGUSR2);
        return g_wd_p_error;
    }
    
    if (SUCCESS != SetArgv(argv))
    {
#ifndef NDEBUG
        write(1, "Error: SetArgv failed\n", 23);
#endif
        kill(pid_to_kill, SIGUSR2);
        return g_wd_p_error;
    }
    
    scheduler_wd = SchedulerCreate();
    if (NULL == scheduler_wd) 
    {
#ifndef NDEBUG
        write(1, "Error: SchedulerCreate failed\n", 31);
#endif
        kill(pid_to_kill, SIGUSR2);
        return (SCHEDULER_CREATE_ERROR);
    }
    /* to change threshold to argv */
    wd_task = SchedulerAddTask(scheduler_wd, WatchDogPong,
                    (void *)threshold, NULL, NULL, time_interval);
    if (UidIsEqual(wd_task, bad_uid))
    {
#ifndef NDEBUG
        write(1, "Error: SchedulerAddTask failed\n", 32);
#endif
        kill(pid_to_kill, SIGUSR2);
        return BAD_UID;
    }
    
    if (FAIL == SetSignals())
	{
#ifndef NDEBUG
        write(1, "Error: SetSignals failed\n", 26);
#endif
        kill(pid_to_kill, SIGUSR2);
		return FAIL;
	}	
    
    sem_post(g_watch_dog_build_sem);
    sem_post(g_ipc_semaphore);

    if (SUCCESS != SchedulerRun(scheduler_wd))
    {
        return FAIL;
    }
    UNUSED(argc);
    UNUSED(envp);
    return (0);
}

int WatchDogPong(void *task_param)
{
	size_t threshold = (size_t )task_param;
    atomic_fetch_add(&g_watchdog_counter, 1);
#ifndef NDEBUG
    write(1,"wd: ping\n", 10);
#endif
    kill(pid_to_kill, SIGUSR1);
    
    if (g_watchdog_counter >= threshold)
	{
        pid_t client_pid = fork();
        int ret_value = 0;
        char *argv[9] = {'\0'};
        if (0 > client_pid)
		{
			return FAIL; 
		}    
		if (0 == client_pid)
		{
            argv[0] = name_of_process;
            argv[1] = NULL;

			ret_value = execv(executable, argv);
			if (0 > ret_value)
            {
                g_wd_p_error = EXEC_FAIL;
#ifndef NDEBUG
				perror("execv abort");
#endif
				abort();
			}
        }
        else
        {
            atomic_fetch_sub(&g_watchdog_counter, g_watchdog_counter);
#ifndef NDEBUG
            write(1, "reviving client\n", 17);
#endif
            waitpid(pid_to_kill, NULL,WNOHANG);
            pid_to_kill = client_pid;
            sem_post(g_watch_dog_build_sem);
            sem_wait(g_ipc_semaphore);
        }
	}
	return SUCCESS;
}

void WatchDog(int sig, siginfo_t *info, void *data)
{
    UNUSED(data);
    UNUSED(info);
    if (sig == SIGUSR1)
    {
        atomic_fetch_sub(&g_watchdog_counter, g_watchdog_counter);
    }

}
void StopTheParty(int sig, siginfo_t *info, void *data)
{
    UNUSED(data);
    UNUSED(info);
    if (sig == SIGUSR2)
    {
        SchedulerAddTask(scheduler_wd, StopTheTrain,NULL,
                         StopTheTrainCleanUp,NULL, 0);
    }
}
static status_ty SetSignals(void)
{
	memset(&sa, 0, sizeof(sa));
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = WatchDog;
    if (0 != sigaction(SIGUSR1, &sa, NULL))
	{
		return FAIL;
	}
    memset(&sa2, 0, sizeof(sa2));
    sa2.sa_flags = SA_SIGINFO;
    sa2.sa_sigaction = StopTheParty;
    if (0 != sigaction(SIGUSR2, &sa2, NULL))
	{
		return FAIL;
	}
    return SUCCESS;
}
static int StopTheTrain(void *param)
{
    UNUSED(param);
    SchedulerStop(scheduler_wd);

    return (FAIL);
}

static void StopTheTrainCleanUp(void *param)
{
    UNUSED(param);
#ifndef NDEBUG
    write(1, "in cleanup\n", 12);
#endif
    sem_close(g_ipc_semaphore);
    sem_close(g_watch_dog_build_sem);
    SchedulerClear(scheduler_wd);
    SchedulerDestroy(scheduler_wd);
}

static status_ty SemaphoreConfigurations(const char *g_sem_name, const char *g_wd_sem)
{
    g_ipc_semaphore = sem_open(g_sem_name, 0);
    if (g_ipc_semaphore == SEM_FAILED)
	{
#ifndef NDEBUG
		perror("sem_open");
#endif
		return FAIL;
	}
    g_watch_dog_build_sem = sem_open(g_wd_sem, 0);
    if (g_watch_dog_build_sem == SEM_FAILED)
	{
#ifndef NDEBUG
		perror("sem_open");
#endif
		return FAIL;
	}
	return SUCCESS;
}

static status_ty SetEnv(void)
{
    if (SUCCESS > sprintf(wd_pid_buff, "%d", getpid()))
    {
        g_wd_p_error = FAILED;
#ifndef NDEBUG
        perror("sprintf");
#endif
		return FAIL;
    }
    if (SUCCESS != setenv("WD_PID", wd_pid_buff, 1))
    {
        g_wd_p_error = SET_ENV_FAIL;
#ifndef NDEBUG
        perror("setenv");
#endif
        return FAIL;
    }
    return  SUCCESS;
}   

static status_ty SetArgv(char *argv[])
{
    time_interval = atoi(argv[1]);
    threshold = atoi(argv[2]);
    pid_to_kill = atoi(argv[3]);
    
    if(NULL == strcpy(executable, argv[4]))
    {
        g_wd_p_error = FAILED;
#ifndef NDEBUG
        perror("strcpy");
#endif
        return FAIL;
    }
    if(NULL == strcpy(name_of_process, argv[5]))
    {
        g_wd_p_error = FAILED;
#ifndef NDEBUG
        perror("strcpy");
#endif
        return FAIL;
    }
    return  SUCCESS;
}
