/****************************************************
* simpleShell                                       *
* Assaf Ainhoren                                    *
* Reviewer: Haggai Newman                           *
* date: 18.07.2022                                  *
****************************************************/
/********************************libraries includes****************************/
#include <stdio.h> /* fgets, puts */
#include <stdlib.h> /* system */
#include <string.h> /*fgets */
#include <sys/types.h> /* pid_t */
#include <unistd.h>  /* fork */
#include <sys/wait.h> /* wait */
#include <ctype.h> /* isspace */

static void InitArgs(char **args, char *buffer);
static void CreateProcess(char **arg_list);
int SimpleShell(int to_run_with_fork);

int main(void)
{
    int to_run_with_fork = 0;
    char answer = 0;
    
    puts("choose if to run commands via fork or system?(type 'f' or 's')");  
    system("stty -icanon -echo");
    answer = getchar();
    system("stty icanon echo");

    if ('f' == answer)
    {
        to_run_with_fork = 1;
    }
    return (SimpleShell(to_run_with_fork));
}

int SimpleShell(int to_run_with_fork)
{
    char buffer[1024] = {'\0'};
    char fork_buffer[1024] = {'\0'};
    const char to_exit[] = "exit";
    char *args[1024] = {""};
    int ret_value = 0;
    
    puts("enter a command you want to run or exit to exit:");
    while (0 != strncmp(buffer, to_exit, strlen(to_exit)))
    { 
        if (to_run_with_fork)
        {
            /* % wildcard %[^\n] tells the function to ignore \n
               %*c take chars as input */
            fscanf(stdin, "%[^\n]%*c", fork_buffer);
            if (0 != strncmp(fork_buffer, to_exit, 4))
            {
                InitArgs(args, fork_buffer);
                CreateProcess(args);
            }
            else
            {
                /* inorder to update the event loop */
                strcpy(buffer, to_exit);
            }
        }
        else
        {
            fgets(buffer, 1024, stdin);
            ret_value = system(buffer);
            if (0 != ret_value)
            {
                printf("the command: %s failed and returned %d\n",buffer,
                                                            ret_value);
            }
        }
    }
    puts("finished successfully");
    return (0);
}


static void CreateProcess(char **arg_list)
{
    pid_t child_pid = fork();
    int ret_value = 0;
    
    if (0 == child_pid)
	{
        ret_value = execvp(*arg_list, arg_list);
		if (0 > ret_value)
		{
			printf("%s Invalid command/command not found\n", arg_list[0]);
			exit (0);
		}
	}
	else if (0 < child_pid)
	{
		wait(&ret_value);
	}
	else
	{
		printf("process failed");
		exit (0);
	}
}


static void InitArgs(char **args, char *buffer)
{
   	while ('\0' != *buffer)
	{
		while (isspace(*buffer))
		{
			*buffer = '\0';
            ++buffer;

		}		
		
        *args = buffer;
        ++args;
		
        while ('\0' != *buffer && !isspace(*buffer))
		{
			++buffer;
		}
	}
	*args = '\0';
}