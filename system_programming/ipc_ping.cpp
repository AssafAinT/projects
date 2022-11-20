#include <fcntl.h> /* For O_* constants */
#include <sys/stat.h>  /* For mode constants*/
#include <semaphore.h> /* semaphore system calls */
#include <cstddef>
#include <cstdio>
#include <cstring>
#define MAX_SEM_NAME 254
#define IGNORE_DOT_SLASH 2
typedef enum {
    SUCCESS        = 0, 
    FAIL           = 1,
	MALLOC_FAILURE = 2
} status_ty;

static status_ty SemaphoreConfigurations(void);
static status_ty GeneralErrorHandling(const char *error);
static sem_t *g_ping_semaphore = NULL;
static const char *g_sem_name = "ping_sem";
static sem_t *g_pong_semaphore = NULL;
static const char *g_pong_name = "pong_sem";



static status_ty SemaphoreConfigurations(void)
{
	int value = 1;
	
    sem_unlink(g_sem_name);
    
    g_ping_semaphore = sem_open(g_sem_name, O_CREAT , 0644, value);
    if (g_ping_semaphore == SEM_FAILED)
    {
        return (GeneralErrorHandling("sem_open"));
    }
    g_pong_semaphore = sem_open(g_pong_name, O_CREAT , 0644, 0);
    if (g_pong_semaphore == SEM_FAILED)
    {
        return (GeneralErrorHandling("sem_open"));
    }
	
	return SUCCESS;
}

static status_ty GeneralErrorHandling(const char* error)
{
#ifndef NDEBUG
	perror(error);
#endif
	return FAIL;
}

int main(void)
{
    if(SUCCESS != SemaphoreConfigurations())
    {
        return FAIL;
    }
    size_t cntr = 10;
    while (0 != cntr)
    {
        sem_wait(g_pong_semaphore);
        
        printf("ping\n");
        --cntr;
        sem_post(g_ping_semaphore);
    }
    sem_close(g_ping_semaphore);    


    return SUCCESS;
}
