#include <stdio.h> /* fgets, puts */
#include <stdlib.h> /* system */
#include <string.h> /*fgets */
#include <sys/types.h> /* pid_t */
#include <unistd.h>  /* fork */
#include <sys/wait.h> /* wait */
#include <ctype.h> /* isspace */
#include <signal.h> /* signal */
static pid_t pid = 0;
sig_atomic_t counter = 0;
void ParentHandler(int sig);
int main(int argc, char **argv)
{
    pid = atoi(argv[1]);
    
    kill(pid, SIGUSR1);
    
    while (4 > counter)
    {
        signal(SIGUSR2,ParentHandler);
        kill(pid, SIGUSR1);
        pause();
        ++counter;
    }
    return 0;
}

void ParentHandler(int sig)
{
    if (sig == SIGUSR2)
    {
        sleep(1);
        write(1,"Exe parent: pong\n", 18);
    }   
}
