#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* pipes, fork */
#include <sys/types.h> /* pid_t */
#include <errno.h> /* errno */

int g_pipe_fd[2] = {0};
int read_pipe_fds[2] = {0};

void OpenPipes(void);


int main(int argc, char **argv)
{
    OpenPipes();

    pid_t pid = fork();
    if (0 == pid)
    {
        /* this is the child proccess! */
        char message[6] = {0};
        close(g_pipe_fd[1]);
        close(read_pipe_fds[0]);

        while (read(g_pipe_fd[0], message, 6) > 0)
        {
            printf("%s", message);
            write(read_pipe_fds[1], ".", 1);
        }

        close(g_pipe_fd[0]);
        close(read_pipe_fds[1]);


    }
    else
    { 
        char buff[1] = {0};

        close(g_pipe_fd[0]);
        close(read_pipe_fds[1]);

        for(size_t i = 0; i < 10; ++i)
        {
            printf("Ping!\n");
            write(g_pipe_fd[1], "Pong!\n", 6);
            read(read_pipe_fds[0], buff, 1);
        }

        close(g_pipe_fd[1]);
        close(read_pipe_fds[0]);
    }

    return 0;
}

void OpenPipes(void)
{
    if (0 != pipe(g_pipe_fd))
    {
        perror("pipe creation failed");
        exit(errno);
    }

    if (0 != pipe(read_pipe_fds))
    {
        perror("pipe creation failed");
        exit(errno);
    }
}
