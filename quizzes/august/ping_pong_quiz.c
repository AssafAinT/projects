/****************************************************
* ping_pong_quiz                                    *
* Assaf Ainhoren                                    *
* Reviewer: Ester Shpoker                           *
* date: 18.07.2022                                  *
****************************************************/
/********************************libraries includes****************************/
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

#define UNUSED(x) (void)(x)

void *DoPing(void *arg);
void *DoPong(void *arg);
static sem_t sem_ping = {0};
static sem_t sem_pong = {0};
static size_t ping_cnt  = 5;
static size_t pong_cnt  = 5;

int main(void)
{
    pthread_t ping_thread = 0;
    pthread_t pong_thread = 0;

    sem_init(&sem_ping, 0 , 1);
    sem_init(&sem_pong, 0 , 0);
    
    pthread_create(&ping_thread, NULL,
            DoPing, NULL);
    pthread_create(&pong_thread, NULL,
            DoPong, NULL);

    pthread_join(ping_thread, NULL);
    pthread_join(pong_thread, NULL);
    return (0);
}

void *DoPing(void *arg)
{
    pthread_key_t key;
    int spec = 1;
    pthread_key_create(&key, NULL);
    pthread_setspecific(key, &spec);

    UNUSED(arg);
    while (ping_cnt)
    {
        sem_wait(&sem_ping);
        printf("PING\n");
        sem_post(&sem_pong);
        --ping_cnt;
    }
    return (NULL);
}

void *DoPong(void *arg)
{
    UNUSED(arg);
    while (pong_cnt)
    {
        sem_wait(&sem_pong);
        printf("PONG\n");
        sem_post(&sem_ping);
        --pong_cnt;

        
    }
    return (NULL);
}