#include <stdio.h>
#include "g.h"



int main()
{
	printf("g_s is %d\n", g_s);
	printf("g_s is %d\n", foo(g_s));

	return(0);	
}


