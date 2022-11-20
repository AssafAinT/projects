#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h> /* pipes, fork */
#include <sys/types.h> /* pid_t */
#include <errno.h> /* errno */

int pipe_fds_g[2] = {0};

void Pong();


int main(void)
{
    printf("PONG HERE!\n");
    Pong();
    return (0);
}


void Pong()
{
    char buff[10] = {0};
    while('.' != *(fgets(buff, 6, stdin)))
    {
        puts(buff);
    }
}
