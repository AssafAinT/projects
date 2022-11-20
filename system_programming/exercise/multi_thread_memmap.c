#include <stdio.h>
#include <pthread.h>
#include <inttypes.h>
#include <unistd.h>

#define N 2

__thread int myVar;
int *commonVar;

void *th(void *arg);
int main(void)
{
        int a = 123;
        pthread_t t[N];
        int arg[N];
        commonVar = &a;

        printf("size of pointer: %lu bits\n", 8UL * sizeof(&a));
        for (int i = 0; i < N; i++)
        {
                arg[i] = i;
                pthread_create(&t[i], 0, th, arg + i);
        }
        for (int i = 0; i < N; i++)
                pthread_join(t[i], 0);
        printf("all done\n");
}

void *th(void *arg)
{
        int myid = *((int *)arg);
        myVar = myid;
        printf("thread %d set myVar=%d, &myVar=%p\n", myid, myVar, &myVar);
        sleep(1);
        printf("thread %d now has myVar=%d\n", myid, myVar);
        sleep(1 + myid);
        printf("thread %d sees this value at *commonVar=%d, commonVar=%p\n", myid, *commonVar, commonVar);
        commonVar = &myVar;
        printf("thread %d sets commonVar pointer to his myVar and now *commonVar=%d, commonVar=%p\n", myid, *commonVar, commonVar);
}