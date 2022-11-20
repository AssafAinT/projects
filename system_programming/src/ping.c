#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h> 
#include <stdlib.h> /*exit */
#include <sys/wait.h> /* wait */
#include <sys/syscall.h>

#define UNUSED(x) (void)x
void ChildHandler(int sig, siginfo_t *info, void *data);

int main(void)
{
    sig_atomic_t counter = 0;
    struct sigaction sa;
    char buffer[1024] = {'\0'};
    
    memset(&sa, 0, sizeof(sa));
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = ChildHandler;
    sigaction(SIGUSR1, &sa, NULL);
    sprintf(buffer, "./pong.out %d", getpid());
    system(buffer);

    return (0);
}

void ChildHandler(int sig, siginfo_t *info, void *data)
{
    UNUSED(data);
    if (sig == SIGUSR1)
    {
        write(1,"Exe child: ping\n", 16);
        sleep(1);    
        kill((pid_t)info->si_pid, SIGUSR2);
    }   
}
