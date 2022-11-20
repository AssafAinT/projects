/****************************************************
* producers_consumers                               *
* Assaf Ainhoren                                    *
* Reviewer: Ester Shpoker                           *
* date: 18.07.2022                                  *
****************************************************/
/********************************libraries includes****************************/
#include <stdio.h>  /* printf */
#include <assert.h> /* assert */
#include <stdlib.h> 
#include <string.h> /* strlen */
#include <sys/stat.h> /* For mode constants */
#include <semaphore.h> /*sem_t */
#include <pthread.h> /* pthread library */
#include <unistd.h> /* sleep */
#include <omp.h> /* omp */
#include <utils.h> /* status_ty */
#include <stdatomic.h>

#include "slist.h"
#include "cbuff.h"

#define UNUSED(x) (void)x
#define NUM_OF_CONSUMERS_AND_PRODUCERS 2
#define LAST_EXERCISE_CONSUMER 5
#define NO_PIZZA 0

static atomic_int g_pizza_slices = 8;
static int g_num_of_pizza = NUM_OF_CONSUMERS_AND_PRODUCERS;
static pthread_mutex_t lock = {0};
static pthread_mutex_t reader_lock = {0};
static pthread_cond_t cond_var = {0};
static sem_t lock_sem = {0};
static sem_t full_sem = {0};
static int ok_to_read = 0;
static int to_read[8] = {0};
static int to_write[5] = {45321, 2345613, 12344567, 123, 11};
static char message[] = "This was the last exercise in multithread!\n";

typedef struct
{
    size_t write;
    size_t read;
    int numbers[5];
} fsq_ty;


static void *NodesTonyVespaRotchild(void *args);
static void *NodesTelAvivConsumer(void *args);
static void *SemTonyVespaRotchild(void *args);
static void *SemTelAvivConsumer(void *args);
static void *TonyVespaRotchild(void *args);
static void *TelAvivConsumer(void *args);
static void *FsqConsumerExer4(void *args);
static void *FsqProducerExer4(void *args);
static void *FsqConsumerExer5(void *args);
static void *FsqProducerExer5(void *args);
static void *FsqConsumerExer6(void *args);
static void *FsqProducerExer6(void *args);

static status_ty FsqExercise(void);
static status_ty RotsChildStreet(void);
static status_ty NodesExer(void);
static status_ty SamMutexExer(void);
static status_ty Exercise5(void);
static status_ty Exercise6(void);
int main(void)
{
    /*assert(SUCCESS == RotsChildStreet());*/
    /*assert(SUCCESS == NodesExer());*/
    /*assert(SUCCESS == SamMutexExer());*/
    /*assert(SUCCESS == FsqExercise());*/
    /*assert(SUCCESS == Exercise6());*/
    return (Exercise6());
}

static status_ty RotsChildStreet(void)
{
    pthread_t pizza_guy = 0;
    pthread_t tel_aviv_boy = 0;

    if(SUCCESS != pthread_create(&pizza_guy, NULL,
                   TonyVespaRotchild, NULL))
    {
        return (FAIL);
    }
    
    if(SUCCESS != pthread_create(&tel_aviv_boy, NULL,
                   TelAvivConsumer, NULL))
    {
        return (FAIL);
    }

    pthread_join(tel_aviv_boy, NULL);
    pthread_join(pizza_guy, NULL);
    return (SUCCESS);
}

static void *TonyVespaRotchild(void *args)
{
    write(1, "New Hot Slices!\n", 17);
    sleep(1);
    while (NO_PIZZA != g_num_of_pizza)
    {
        if (0 == g_pizza_slices)
        {
            atomic_fetch_sub(&g_num_of_pizza, 1);

            if (NO_PIZZA != g_num_of_pizza)
            {
                atomic_fetch_add(&g_pizza_slices, 8);
                write(1, "New Hot Slices!\n", 17);
                sleep(1);
            }
        }
    }
    write(1, "Out Of Pizza!\n", 15);
    sleep(1);
    return (NULL);
}
static void *TelAvivConsumer(void *args)
{
    while (NO_PIZZA != g_num_of_pizza)
    {
        if (0 < g_pizza_slices)
        {
            atomic_fetch_sub(&g_pizza_slices, 1);
            write(1, "I took 1 slice of pizza\n", 25);
        }
        sleep(1);
    }
    return (NULL);
}

static status_ty NodesExer(void)
{
    slist_ty *head = SlistCreate();
    pthread_t consumers_arr[NUM_OF_CONSUMERS_AND_PRODUCERS] = {0};
    pthread_t producers_arr[NUM_OF_CONSUMERS_AND_PRODUCERS] = {0};
    
    int ret_val = 0;
    size_t i = 0;

    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        puts("Couldn't initialize mutex");
        return (FAIL);
    }

    for (i = 0 ;i < NUM_OF_CONSUMERS_AND_PRODUCERS && 
                0 == ret_val; ++i)
    {
        ret_val =  pthread_create(&consumers_arr[i], NULL,
                    NodesTelAvivConsumer, head);
        ret_val =  pthread_create(&producers_arr[i], NULL,
            NodesTonyVespaRotchild, head);
    }

    if (0 == ret_val)
    {
        for ( i = 0; i < NUM_OF_CONSUMERS_AND_PRODUCERS ; ++i)
        {
            pthread_join(consumers_arr[i], NULL);
            pthread_join(producers_arr[i], NULL);
        }
    }
    
    else
    {
        return (FAIL);
    }
    pthread_mutex_destroy(&lock);     
    SlistDestroy(head);
    return SUCCESS;
}

static void *NodesTonyVespaRotchild(void *args)
{
    slist_ty *list = (slist_ty *)args;
    int i = 0;

    pthread_mutex_lock(&lock);       
    while (i < g_pizza_slices)
    {
        SlistInsertBefore(SlistEnd(list), NULL); 
        ++i;
        write(1, "New Hot Slices!\n", 17);
    }
    pthread_mutex_unlock(&lock);
    return (NULL);

}
static void *NodesTelAvivConsumer(void *args)
{
    slist_ty *list = (slist_ty *)args;
    int i = 1;
    while (0 < g_num_of_pizza)
    {    
        pthread_mutex_lock(&lock);
        while (!SlistIsEmpty(list))
        {
            SlistRemove(SlistBegin(list));
            ++i;
            write(1, "I took 1 slice of pizza\n", 25);
            if ( g_pizza_slices == i )
            {
                --g_num_of_pizza;
                i = 0;
            }
        }
        pthread_mutex_unlock(&lock);
    }

    return (NULL);
}

static status_ty SamMutexExer(void)
{
    slist_ty *head = SlistCreate();
    pthread_t consumers_arr[NUM_OF_CONSUMERS_AND_PRODUCERS] = {0};
    pthread_t producers_arr[NUM_OF_CONSUMERS_AND_PRODUCERS] = {0};
    
    int ret_val = 0;
    size_t i = 0;

    sem_init(&lock_sem, 0 , 0);

    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        puts("Couldn't initialize mutex");
        return (FAIL);
    }

    for (i = 0 ;i < NUM_OF_CONSUMERS_AND_PRODUCERS && 
                0 == ret_val; ++i)
    {
        ret_val =  pthread_create(&consumers_arr[i], NULL,
                    SemTelAvivConsumer, head);
    }
    for (i = 0 ;i < NUM_OF_CONSUMERS_AND_PRODUCERS && 
                0 == ret_val; ++i)
    {
        ret_val =  pthread_create(&producers_arr[i], NULL,
            SemTonyVespaRotchild, head);
    }

    if (0 == ret_val)
    {
        for ( i = 0; i < NUM_OF_CONSUMERS_AND_PRODUCERS ; ++i)
        {
            pthread_join(consumers_arr[i], NULL);
        }
        for ( i = 0; i < NUM_OF_CONSUMERS_AND_PRODUCERS ; ++i)
        {
            pthread_join(producers_arr[i], NULL);
        }
    }
    
    else
    {
        return (FAIL);
    }
    pthread_mutex_destroy(&lock);     
    SlistDestroy(head);
    sem_destroy(&lock_sem);
    return SUCCESS;
}


static void *SemTonyVespaRotchild(void *args)
{
    slist_ty *list = (slist_ty *)args;
    int i = 0;
    
    pthread_mutex_lock(&lock);       
    while (i < g_pizza_slices)
    {
        SlistInsertBefore(SlistEnd(list), NULL); 
        atomic_fetch_add(&i, 1);
        write(1, "New Hot Slices!\n", 17);
    }
    sem_post(&lock_sem);
    pthread_mutex_unlock(&lock);
    return (NULL);

}
static void *SemTelAvivConsumer(void *args)
{
    slist_ty *list = (slist_ty *)args;

    sem_wait(&lock_sem);
    pthread_mutex_lock(&lock);
    while (!SlistIsEmpty(list))
    {
        SlistRemove(SlistBegin(list));
        write(1, "I took 1 slice of pizza\n", 25);
    }
    pthread_mutex_unlock(&lock);
    return (NULL);
}

static status_ty FsqExercise(void)
{
    cbuff_ty *pizza_buffer = CBuffCreate(g_pizza_slices * sizeof(int));
    pthread_t consumers_arr[NUM_OF_CONSUMERS_AND_PRODUCERS] = {0};
    pthread_t producers_arr[NUM_OF_CONSUMERS_AND_PRODUCERS] = {0};
    int ret_val = 0;
    size_t i = 0;

    sem_init(&lock_sem, 0 , 0);
    sem_init(&full_sem, 0, g_pizza_slices * sizeof(int));

    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        puts("Couldn't initialize mutex");
        return (FAIL);
    }

    for (i = 0 ;i < NUM_OF_CONSUMERS_AND_PRODUCERS && 
                0 == ret_val; ++i)
    {
        ret_val =  pthread_create(&producers_arr[i], NULL,
            FsqProducerExer4, pizza_buffer);
    }
    for (i = 0 ;i < NUM_OF_CONSUMERS_AND_PRODUCERS && 
                0 == ret_val; ++i)
    {
        ret_val =  pthread_create(&consumers_arr[i], NULL,
                    FsqConsumerExer4, pizza_buffer);
    }

    if (0 == ret_val)
    {
        for ( i = 0; i < NUM_OF_CONSUMERS_AND_PRODUCERS ; ++i)
        {
            pthread_join(consumers_arr[i], NULL);
           
        }
        for ( i = 0; i < NUM_OF_CONSUMERS_AND_PRODUCERS ; ++i)
        {
            pthread_join(producers_arr[i], NULL);
        }
    }
    
    else
    {
        return (FAIL);
    }
    pthread_mutex_destroy(&lock);     
    CBuffDestroy(pizza_buffer);
    sem_destroy(&lock_sem);
    sem_destroy(&full_sem);
    return SUCCESS;
}
static void *FsqProducerExer4(void *args)
{
    cbuff_ty *buffer = NULL;
    int i = 1;
    buffer = (cbuff_ty *)args;
    pthread_mutex_lock(&lock); 
    while (i <= g_pizza_slices)
    {      
        sem_wait(&full_sem);
        CBuffWrite(buffer, (char *)&i, sizeof(int));
        ++i;
    }
    sem_post(&lock_sem);
    pthread_mutex_unlock(&lock);
    sem_post(&full_sem);
    return (NULL);
}
static void *FsqConsumerExer4(void *args)
{
    cbuff_ty *buffer = NULL;
    int i = 0;
    buffer = (cbuff_ty *)args;
    pthread_mutex_lock(&lock);       
    while (i < g_pizza_slices)
    {      
        CBuffRead(buffer, (char *)&to_read[i], sizeof(int));
        printf("%d\n", to_read[i]);
        ++i;

    }
    sem_post(&lock_sem);
    pthread_mutex_unlock(&lock);
    return (NULL);
}

static status_ty Exercise5(void)
{
    fsq_ty fsq = {0, 0, {0}};
    pthread_t consumers_arr[5] = {0};
    pthread_t producers_arr[5] = {0};
    int ret_val = 0;
    size_t i = 0;

    sem_init(&full_sem, 0, 5);
    sem_init(&lock_sem, 0 , 0);
    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        puts("Couldn't initialize mutex");
        return (FAIL);
    }
    if (pthread_mutex_init(&reader_lock, NULL) != 0)
    {
        puts("Couldn't initialize mutex");
        return (FAIL);
    }
    for (i = 0 ;i < 5 && 
                0 == ret_val; ++i)
    {
        ret_val =  pthread_create(&consumers_arr[i], NULL,
                    FsqConsumerExer5, &fsq);
    }
    for (i = 0 ;i < 5 && 
                0 == ret_val; ++i)
    {
        ret_val =  pthread_create(&producers_arr[i], NULL,
            FsqProducerExer5, &fsq);
    }

    if (0 == ret_val)
    {
        for ( i = 0; i < 5 ; ++i)
        {
            pthread_join(consumers_arr[i], NULL);
        }
        for ( i = 0; i < 5 ; ++i)
        {
            pthread_join(producers_arr[i], NULL);
        }
    }
    
    else
    {
        return (FAIL);
    }
    pthread_mutex_destroy(&lock);     
    sem_destroy(&lock_sem);
    sem_destroy(&full_sem);
    return SUCCESS; 
}
static void *FsqProducerExer5(void *args)
{
    fsq_ty *buffer = (fsq_ty *)args;
    sem_wait(&full_sem);
    pthread_mutex_lock(&lock); 
    buffer->numbers[buffer->write] = to_write[buffer->write];
    buffer->write = (buffer->write +1);
    pthread_mutex_unlock(&lock);
    sem_post(&lock_sem);
    return (NULL);
}
static void *FsqConsumerExer5(void *args)
{
    fsq_ty *buffer = (fsq_ty *)args;
    sem_wait(&lock_sem);
    pthread_mutex_lock(&reader_lock);       
    printf("%d\n",buffer->numbers[buffer->read]);
    buffer->read = (buffer->read + 1);
    pthread_mutex_unlock(&reader_lock);
    return (NULL);
}
static status_ty Exercise6(void)
{
    char buffer[45] = {'\0'};
    pthread_t producer_thread = 0;
    pthread_t consumers_arr[LAST_EXERCISE_CONSUMER] = {0};
    int ret_val = 0;
    size_t i = 0;
    pthread_cond_init(&cond_var, NULL);
    sem_init(&lock_sem, 0 , 0);
    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        puts("Couldn't initialize mutex");
        return (FAIL);
    }
    ret_val =  pthread_create(&producer_thread, NULL,
            FsqProducerExer6, &buffer);
    
    for (i = 0 ;i < LAST_EXERCISE_CONSUMER && 
                0 == ret_val; ++i)
    {
        ret_val =  pthread_create(&consumers_arr[i], NULL,
            FsqConsumerExer6, &buffer);
    }
    if (0 == ret_val)
    {
        pthread_join(producer_thread, NULL);
        for ( i = 0; i < LAST_EXERCISE_CONSUMER ; ++i)
        {
            pthread_join(consumers_arr[i], NULL);
        }
    }
    else
    {
        return (FAIL);
    }
    return (SUCCESS);
}

static void *FsqProducerExer6(void *args)
{
    char *buffer = (char *)args;
    size_t i =0;
    strcpy(buffer, message);
    ok_to_read = 1;
    pthread_cond_broadcast(&cond_var);
    for ( ; i < LAST_EXERCISE_CONSUMER ; ++i)
    {
        sem_wait(&lock_sem);
    }
    printf("done producer_thread\n");
    ok_to_read = 0;
    return (NULL);
}
static void *FsqConsumerExer6(void *args)
{
    char *buffer = (char *)args;
    
    pthread_mutex_lock(&lock); 
    if (!ok_to_read)
    {
        pthread_cond_wait(&cond_var, &lock);
    }
    write(1, buffer, 45);
    pthread_mutex_unlock(&lock);
    sem_post(&lock_sem);
    return (NULL);
}