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
#include <sys/wait.h> /* wait */

sig_atomic_t sig_usr_counter = 0;
void ParentHandler(int sig);
void ChildHandler(int sig);
void PingPongFork(void);
void PingPongForkAndExec(void);

int main(void)
{
    PingPongFork();
    return (0);
}
void PingPongForkAndExec(void)
{

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
    
}

void ParentHandler(int sig)
{
    if (sig == SIGUSR2)
    {
        puts (" parent: pong");
    }
}

void ChildHandler(int sig)
{
    if (sig == SIGUSR1)
    {
        puts (" child: ping");
        sleep(1);
        kill(getppid(), SIGUSR2);
    }
}

