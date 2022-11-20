#include <stdio.h>
#include "printit.h"

const int con_data = 215; 
static stat_glob_data = 226;

void Foo(int num_to_print)
{
	printf("Printing the const data\n", con_data);
	printf("%d is the num you asked to print\n", num_to_print);
}
