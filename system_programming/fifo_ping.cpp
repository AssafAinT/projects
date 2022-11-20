#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* pipes, fork */
#include <sys/types.h> /* pid_t */
#include <errno.h> /* errno */
#include <sys/stat.h>
#include <fcntl.h>
int main(void)
{
    if((mkfifo("/home/assaf/git/system_programming/fifo/fifo_one", S_IRWXU | S_IRWXG))!=-1)
    {
        printf("Pipe opened.\n");
    }
    else
    {
        perror("Could not open pipe.");
    }
    int fifo_ping = 0;
    size_t cntr = 10;
    char buf[1024] = {0};
    
    while (cntr != 0)
    {
        fifo_ping = open("/home/assaf/git/system_programming/fifo/fifo_one", O_WRONLY);
        write(fifo_ping, "ping", 5);
        
        close(fifo_ping);
        
        fifo_ping = open("/home/assaf/git/system_programming/fifo/fifo_one", O_RDONLY);
        if (read(fifo_ping, buf, 5) > 0)
        {
            puts(buf);
            sleep(5);
        }
        --cntr;
        close(fifo_ping);
    }

    unlink("/home/assaf/git/system_programming/fifo/fifo_one");
}