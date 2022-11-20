#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h> 
#include <stdlib.h> /*exit */
#include <sys/wait.h> /* wait */

void ExecChildHandler(int sig);
int main(void)
{
    sig_atomic_t counter = 0;
    while (4 > counter)
    {
        signal(SIGUSR1,ExecChildHandler);
        pause();
        ++counter;
    }
    return (0);
}

void ExecChildHandler(int sig)
{
    if (sig == SIGUSR1)
    {
        write(1,"Exe child: pong\n", 17);
        sleep(1);
        kill(getppid(), SIGUSR2);
    }   
}
