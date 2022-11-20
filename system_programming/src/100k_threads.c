/****************************************************
* 100k_Threads                                      *
* Assaf Ainhoren                                    *
* Reviewer: Ester Shpoker                           *
* date: 18.07.2022                                  *
****************************************************/
/********************************libraries includes****************************/
#include <stdio.h>  /* printf */
#include <assert.h> /* assert */
#include <stdlib.h> 
#include <pthread.h> /* pthread library */
#include <unistd.h> /* sleep */
#include <semaphore.h> /* sem_t */
#include <omp.h> /* omp */
#define ONE_THOUSAND_K  100000
#define TWENTY_THOUSAND_K 25000
#define THIRTY_K 30000
#define NUM_THREADS 10

static const size_t g_interval = 4;
int i = 0;
static void ThreadCreate(void);
static void ThreadOptimize(void);
static void ThreadOptialNum(void);
static void *RoutineWithOutPutin(void *args);
static void *InsertToArr(void *args);
static void Assert(void);
static void Print(void);
static void *SumOfDivisors(void *num);
static void *OptSumOfDivisors(void *num);
static void *VarThreadsSumOfDivisors(void *num);

static int array[ONE_THOUSAND_K] = {0};

static pthread_t threads_arr[ONE_THOUSAND_K] = {0};
static pthread_t threads_arr1[THIRTY_K] = {0};

static const size_t number_exe4 = 1234567891;
static const size_t partition = (number_exe4 / NUM_THREADS) + 1;

int main(void)
{
    /*ThreadOptimize();*/
    ThreadOptialNum();
    /*ThreadCreate();*/
    return (0);
}

static void *RoutineWithOutPutin(void *args)
{
    printf("the value of arg is %d\n", *(int *)args);

    pthread_exit(NULL);
}

static void *InsertToArr(void *args)
{
    array[(int)args] = (int )args;

    pthread_exit(NULL);
}

static void Assert(void)
{
    size_t i = 0;
    for ( ; i < ONE_THOUSAND_K; ++i)
    {
        assert(i == (size_t)array[i]);
    }
}

static void Print(void)
{
    size_t i = 0;
    for ( ; i < ONE_THOUSAND_K; ++i)
    {
        printf("%d\n", array[i]);
    }
}

static void ThreadCreate(void)
{
    pthread_attr_t attr;
    pthread_t thread = 0;
    size_t i = 0; 
    size_t j = 0;
    size_t current_i = 0;
    size_t prev_i = 0;
    time_t start_time = time(&start_time);
    int ret_val = 0;
    /* for exercise 3 */
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    /* exercise 3 */
    for (i = 0; i < g_interval; ++i)
    {
        for ( j = 0; j < TWENTY_THOUSAND_K && 0 == ret_val; ++j, ++current_i)
        {
            ret_val =  pthread_create(&threads_arr[current_i], &attr,
                          InsertToArr, (void *)current_i);
            
        }
        /* exercise 2  */
        /* if ( 0 == ret_val)
        {
            for ( j = 0; j < TWENTY_THOUSAND_K ; ++j, ++prev_i)
            {
                pthread_join(threads_arr[prev_i], NULL);
            }
        }*/
    }
    
    printf("the task took %f seconds\n",
        difftime(time(NULL), start_time));
    sleep(2);
    Print();
    Assert();
    pthread_attr_destroy(&attr);
}

static void ThreadOptimize(void)
{
    size_t i = 0; 
    size_t number = number_exe4;
    size_t sum_of_divisors = 0;
    int *num_of_divisor = NULL;
    int ret_val = 0;

    for (i = 0 ; i <= (number / 100000) && 0 == ret_val; ++i)
    {
        ret_val =  pthread_create(&threads_arr1[i], NULL,
                    SumOfDivisors, (void *)((i + 1)*(100000)));
    }
    if ( 0 == ret_val)
    {
        for ( i = 0; (i <= (number / 100000)) ; ++i)
        {
            pthread_join(threads_arr1[i], (void **)&num_of_divisor);
    
            sum_of_divisors += (size_t )num_of_divisor;
        }
    }

    printf("the number of threads: %lu\n", i);
    printf("the sum of divisor for 1234567891 is %lu\n", sum_of_divisors);
}

static void *SumOfDivisors(void *num)
{
    int sum_of_divisors = 0;
    int num_to_div = (int )num;
    int i = num_to_div - 100000 + 1;

    for ( ; i <= num_to_div; ++i)
    {
        if ( 0 == number_exe4 % i)
        {
            sum_of_divisors += i;
        }
    }
    
    return((void *)sum_of_divisors);
}

static void ThreadOptialNum(void)
{
    pthread_t thread = 0;
    pthread_t threads_arr2[NUM_THREADS];
    size_t i = 0; 
    size_t num_to_send = 1;
    size_t sum_of_divisors = 0;
    size_t num_of_divisor = 0;
    size_t number = number_exe4;
    int ret_val = 0;
    
    for (i = 0 ;i < NUM_THREADS && 
                0 == ret_val; ++i)
    {
        ret_val =  pthread_create(&threads_arr2[i], NULL,
                    VarThreadsSumOfDivisors, (void *)(i * partition));
    }
    if ( 0 == ret_val)
    {
        for ( i = 0; i < NUM_THREADS ; ++i)
        {
            pthread_join(threads_arr2[i], (void **)&num_of_divisor);
    
            sum_of_divisors += num_of_divisor;
        }
    }
    
    printf("the number of threads: %lu\n", i);
    printf("the sum of divisor for 1234567891 is %lu\n", sum_of_divisors);
    
    /*ret_val =  pthread_create(&thread, NULL,
                    OptSumOfDivisors, (void *)number);
    
    pthread_join(thread, (void **)&num_of_divisor);
    
    
    printf("the number of threads: %lu\n", i);
    printf("the sum of divisor for 1234567891 is %lu\n", num_of_divisor);*/
   
}

static void *OptSumOfDivisors(void *num)
{
    int sum_of_divisors = 0;
    int num_to_div = (int )num;
    int i = 0;
    
    for (i = 1; i <= num_to_div; ++i)
    {
        if ( 0 == number_exe4 % i)
        {
            sum_of_divisors += i;
        }
    }
    
    return((void *)sum_of_divisors);
}

static void *VarThreadsSumOfDivisors(void *num)
{
    size_t lower_bound = 0;
    size_t upper_bound = (size_t)num + 1 + partition;  
    size_t sum_of_divisors = 0;
    
    upper_bound = (upper_bound > number_exe4) ? number_exe4 : upper_bound; 
#pragma omp parallel for
    for ( lower_bound = ((size_t)num + 1) ;
          lower_bound  <= upper_bound;
          ++lower_bound)
    {
        if (0 == number_exe4 % lower_bound)
        {
            #pragma omp critical
            {
                sum_of_divisors += lower_bound;
            }
        }
    }
    return ((void *)sum_of_divisors);
}