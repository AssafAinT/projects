/****************************************************
* ping_pong                                         *
* Assaf Ainhoren                                    *
* Reviewer: Ester Shpoker                           *
* date: 18.07.2022                                  *
****************************************************/
/********************************libraries includes****************************/
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h> 
#include <stdlib.h> /*exit */
#include <sys/wait.h> /* wait */

sig_atomic_t sig_usr_counter = 0;
void ParentHandler(int sig);
void ChildHandler(int sig);
void PingPongFork(void);
void PingPongForkExec(void);

int main(void)
{
    PingPongForkExec();
    puts("execvp done");
    sig_usr_counter = 0;
    PingPongFork();
    return (0);
}
void PingPongForkExec(void)
{
    pid_t pong_pid = fork();
    int ret_value = 0;
    if (0 > pong_pid)
    {
        puts("fork failed");
        return ; 
    }    

    if (0 == pong_pid)
    {
        ret_value = execvp("do_ping_pong", NULL);
        if (0 > ret_value)
        {
            printf("Invalid command/command not found\n");
            abort();
        }
    }
    else
    {
        while (4 > sig_usr_counter)
        {
            signal(SIGUSR2,ParentHandler);
            sleep(1);
            kill(pong_pid, SIGUSR1);
            wait(&ret_value);
            ++sig_usr_counter;
        }
    }
}

void PingPongFork(void)
{
    pid_t child_pid = fork();
    int ret_value = 0;

    if (0 > child_pid)
    {
        puts("fork failed");
        return ; 
    }

    while (4 > sig_usr_counter)
    {
        if (0 == child_pid)
        {
            signal(SIGUSR1,ChildHandler);
            pause();
        }
        else if (0 < child_pid)
        {
            signal(SIGUSR2,ParentHandler);
            sleep(1);
            kill(child_pid, SIGUSR1);
            pause();            
        }
        ++sig_usr_counter;
    }
    sig_usr_counter = 0;
}

void ParentHandler(int sig)
{
    if (sig == SIGUSR2)
    {
        write(1, "parent: ping\n", 14);
    }
}

void ChildHandler(int sig)
{
    if (sig == SIGUSR1)
    {
        write(1, "child: ping\n", 14);
        sleep(1);
        kill(getppid(), SIGUSR2);
    }
}

