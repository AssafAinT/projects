#include <stdio.h> /* fgets, puts */
#include <stdlib.h> /* system */
#include <string.h> /*fgets */
#include <sys/types.h>
#include <unistd.h> 
#include <sys/wait.h> /* wait */
#include <ctype.h> /* isspace */
static int SimpleShellFork(void);
static void InitArgs(char **args, char *buffer);
static int CreateProcess(char **arg_list);
int main (void)
{
    /*char* arg_list[] = { "ls", "-l", "/", NULL};


    Spawn ("ls", arg_list);
    printf ("done with main program\n");*/
    return (SimpleShellFork());
} 
int SimpleShellFork(void)
{
    char buffer[1024] = {'\0'};
    const char to_exit[] = "exit";
    char *args[1024] = {""};

    puts("enter a command you want to run or exit to exit:");
    while (0 != strncmp(buffer, to_exit, strlen(to_exit)))
    {
        /* % wildcard %[^\n] tells the function to ignore \n
         %*c take chars as input */
        fscanf(stdin, "%[^\n]%*c", buffer);
        InitArgs(args, buffer);
        CreateProcess(args);

        puts("enter a command you want to run or exit to exit:");
    }
    puts("finished successfully");
    return (0);
    
} 

static int CreateProcess(char **arg_list)
{
    pid_t child_pid = fork();
    int ret_value = 0;
    
    if (0 == child_pid)
	{
        ret_value = execvp(*arg_list, arg_list);
		if (0 > ret_value)
		{
			printf("%s Invalid command/command not found\n", arg_list[0]);
			
			return (ret_value);
		}
	}
	else if (0 < child_pid)
	{
		wait(&ret_value);
	}
	else
	{
		printf("process failed");
		return (child_pid);
	}
    return (ret_value);
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