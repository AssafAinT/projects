/****************************************************
* sem_manipulation                                  *
* Assaf Ainhoren                                    *
* Reviewer: Ester Shpoker                           *
* date: 18.07.2022                                  *
****************************************************/
/********************************libraries includes****************************/
#include <stdio.h>
#include <assert.h> /* assert */
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h> /*fgets */
#include <ctype.h> /* isspace */

#define RAND_ASCII ((rand() + 1) % 254)

union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};
int SemManipulation(const char *pathname);
int SemInit(key_t key, int n_sems);
void IgnoreSpaces(char *buffer);

int main(int argc, char const *argv[])
{
    SemManipulation(argv[1]);
    return 0;
}

int SemManipulation(const char *pathname)
{
    key_t key = 0;
    int sem_id = 0;
    union semun arg;
    struct semid_ds buf = {0};
    struct sembuf sb = {0};
    char buffer[1024] = {'\0'};
    const char to_exit[] = "X";
    char to_view = 'V';
    assert(NULL != pathname);
    
    if ((key = ftok(pathname, RAND_ASCII) == -1))
    {
        perror("ftok");
        return(1);
    }
    sem_id = SemInit(key, 1);
    if (-1 != sem_id )
    {
        puts("here");
        while ('X' != buffer[0])
        {
            fscanf(stdin, "%[^\n]%*c", buffer);
            if(to_view == *buffer)
            {
                printf("%d is semaphore value \n",semctl(sem_id, sb.sem_flg, GETVAL,arg ));
            }
            else if ('I' == *buffer)
            {
                IgnoreSpaces(buffer);
                arg.val = atoi(buffer);
                semctl(sem_id, sb.sem_flg, SETVAL,arg );
            }
            else if ('D' == *buffer)
            {
                IgnoreSpaces(buffer);
                arg.val = -1 * atoi(buffer);
                semctl(sem_id, sb.sem_flg, SETVAL, arg );
            }
        }
    }
    if (semctl(sem_id, 1, IPC_RMID, arg) == -1)
    {
        perror("semctl");
        return(1);
    }
    return (0);
}

int SemInit(key_t key, int n_sems)
{
    size_t i = 0;
    union semun arg;
    struct semid_ds buf = {0};
    struct sembuf sb = {0};
    char buffer[1024] = {'\0'};
    int sem_id = 0;

    sem_id = semget(key, n_sems, IPC_CREAT | IPC_EXCL | 0666);

    if (0 <= sem_id)
    {
        sb.sem_op =1;
        sb.sem_flg =0;
        arg.val = 1;
        semctl(sem_id, sb.sem_flg, SETVAL, arg);
        /*for (sb.sem_num = 0; sb.sem_num < n_sems; ++sb.sem_num)
        {
            if (semop(sem_id, &sb, 1) == -1) 
            {
                int err = errno;
                semctl(sem_id, 0, IPC_RMID);*/ /* clean up */
                /*errno = err;*/
                /*return (-1);*/ /* error, check errno */
            /*}  
        }*/
    }
    
    /* returning sem_id need to check errno */
    else
    {
        return sem_id;
    }

    return sem_id;
}

void IgnoreSpaces(char *buffer)
{
    ++buffer;
    while (isspace(*buffer))
    {
        puts("Ignoring spaces");
        *buffer = '\0';
        ++buffer;
    }    
}