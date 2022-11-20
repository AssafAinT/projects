#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* pipes, fork */
#include <sys/types.h> /* pid_t */
#include <errno.h> /* errno */
#include <sys/stat.h>
#include <fcntl.h>
int main(void)
{
    int fifo_pong = 0;
    size_t cntr = 10;
    char buf[1024] = {0};
    
    while (cntr != 0)
    {
        fifo_pong = open("/home/assaf/git/system_programming/fifo/fifo_one", O_RDONLY);
        if (read(fifo_pong, buf, 5) > 0)
        {
            puts(buf);
            sleep(5);
        }
        close(fifo_pong);
        fifo_pong = open("/home/assaf/git/system_programming/fifo/fifo_one", O_WRONLY);
        write(fifo_pong, "pong", 5);
        --cntr;
        close(fifo_pong);
    }

}