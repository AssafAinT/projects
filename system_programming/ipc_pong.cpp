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
	g_ping_semaphore = sem_open(g_sem_name, 0);
    if (g_ping_semaphore == SEM_FAILED)
	{
#ifndef NDEBUG
		perror("sem_open");
#endif
		return FAIL;
	}

    sem_unlink(g_sem_name);
    
    g_pong_semaphore = sem_open(g_pong_name, O_CREAT , 0644, 1);
    if (g_pong_semaphore == SEM_FAILED)
    {
#ifndef NDEBUG
		perror("sem_open");
#endif
		return FAIL;

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
        sem_wait(g_ping_semaphore);

        printf("pong\n");
        --cntr;
        sem_post(g_pong_semaphore);
    }
    sem_close(g_pong_semaphore);

    return SUCCESS;
}
