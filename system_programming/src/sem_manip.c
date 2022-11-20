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
#include <fcntl.h> /* For O_* constants */
#include <sys/stat.h> /* For mode constants */
#include <semaphore.h>
#include <string.h> /*fgets */
#include <ctype.h> /* isspace */


int SemManipulation(const char *pathname);
char *IgnoreSpaces(char *buffer);

int main(int argc, char const *argv[])
{
    SemManipulation(argv[1]); 

    return 0;
}

int SemManipulation(const char *pathname)
{
    sem_t *my_semaphore = NULL;
    int value = 0;
    int sem_val = 0;
    char buffer[1024] = {'\0'};
    const char to_exit[] = "X";
    char to_view = 'V';
    int size_to_clean = 0;
    char to_clean = 'y';
    assert(NULL != pathname);

    printf("What do you want the semaphore value to be?\n");
    printf("Semaphore value: ");
    scanf("%d\n", &value);
    
    my_semaphore = sem_open(pathname, O_CREAT , 0644, value);
    if(my_semaphore == SEM_FAILED)
    {
        perror("sem_open");
        return -1;
    }
    else
    {
        assert(0 == sem_getvalue(my_semaphore, &sem_val));
        fscanf(stdin, "%[^\n]%*c", buffer);
        while ('X' != buffer[0])
        {   
            if('V' == buffer[0])
            {
                assert(0 == sem_getvalue(my_semaphore, &sem_val));
                printf("%d is the semaphore value\n",sem_val);
            }
            else if ('I' == buffer[0])
            {
                value = atoi(IgnoreSpaces(buffer));
                if (NULL != strstr(buffer, "undo"))
                {
                    size_to_clean += value;
                    printf("%d is the value to clean\n",size_to_clean);
                }

                for ( ; value > 0; --value)
                {
                    sem_post(my_semaphore);
                }
            }
            else if ('D' == buffer[0])
            {   
                value = atoi(IgnoreSpaces(buffer)); 
                if (NULL != strstr(buffer, "undo"))
                {
                    size_to_clean -= value;
                    printf("%d is the value to clean\n",size_to_clean);
                }
                for ( ; value > 0; --value)
                {
                    sem_wait(my_semaphore);
                }
            }
            fscanf(stdin, "%[^\n]%*c", buffer);
        }
    }
    if ( size_to_clean > 0 )
    {
        for ( ; size_to_clean > 0; --size_to_clean)
        {
            sem_wait(my_semaphore);
        }
    }
    else
    {
        for ( ; size_to_clean < 0; ++size_to_clean)
        {
            sem_post(my_semaphore);
        }
    }
    printf("to perform cleanup? type 'y'\n");
    to_clean = getchar();
    if (to_clean == 'y')
    {
        sem_close(my_semaphore);
        sem_unlink(pathname);
    }
    return (0);
}


char *IgnoreSpaces(char *buffer)
{
    ++buffer;
    while (isspace(*buffer))
    {
        ++buffer;
    } 
    return buffer;   
}
