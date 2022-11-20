#include <stdio.h>
#include <stdlib.h>

#include "printit.h"




int foo(void);
static int choo(void);

const int con_data = 215; 
static stat_glob_data = 226;

int main(int argc, char **argv, char **envp)
{

	int stack_data = 10;
	int stack_data2 = 33;
	int *heap_data = (int *)malloc(sizeof(int));
	int *heap_data2 = (int *)malloc(sizeof(int));
	static int stat_data = 10;
	char *string_lit = "blup";
	int arg_counter = 0;
	size_t i = 0;
	*heap_data = 18;
	*heap_data2 = -22;
	
	Foo(35464);
	/* printing function addresses */
	printf("%0x", foo);
	printf("\n%0x\n", choo);
	foo();
	choo();
	printf("\n0x%lx\n", heap_data);
	printf("\n heap data holds: %d\n", *heap_data);
	printf("\n local stack var holdsholds %p address\n", &stack_data);
	printf("\nglobal const holds %p address\n", &con_data);
	printf("\nlocal static var holds %p address\n", &stat_data);
	printf("\nglobal static var holds %p address\n", &stat_glob_data);
	printf("\nstring literal holds %p address\n", string_lit);
	
	for ( ;arg_counter < argc; ++arg_counter)
	{
		printf("this the %d argument: %s\n",arg_counter, argv[arg_counter]);
	}
	
	for (i = 0; envp[i] != NULL; i++)
    {
        printf("environment var%s\n", envp[i]);
    }    
	free(heap_data);
	free(heap_data2);
	heap_data = NULL;
	return (0);
}

int foo(void)
{
	/*printf("this is an extern func\n");*/
	return (0);
}

static int choo(void)
{
	/*printf("\nthis is a static func\n");*/
	return (0);
}	


