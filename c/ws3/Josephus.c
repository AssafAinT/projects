#include <stdio.h>
#include <stddef.h>
#define SIZE 100

int Joseph(int *arr, size_t size_arr);
int *FindNextAlive(int *start, int *me, size_t size_arr);
void ArrPrint (int *arr, size_t size_arr);

int main()
{
	size_t i =0;
	int arr[SIZE];
	
	while (i<SIZE)
	{
	  arr[i] = 0;
	  ++i;
  	}
  	
	printf("The winnder is at place : %d\n", (Joseph(arr , SIZE)+1));

	ArrPrint(arr, SIZE);
	
	return (0);
			
}

int Joseph(int *arr, size_t size_arr)
{
	int *start = arr;
	int *me = arr;
	size_t moves = 0 ;
	int *alive = NULL;
	
	while ( size_arr - 1 != moves)
	{
		alive = FindNextAlive(start, me , size_arr);
		*alive = 1;                                  /* killing the one's alive */
		++moves;
		alive = FindNextAlive(start, me , size_arr);
		me = alive;                                 /* sword in the next avail spot */
	}
	return ((me - start));
}

int *FindNextAlive(int *start, int *me , size_t size_arr)
{	
	int *end = start + size_arr;
	int *runner = NULL;
	
	if (me == end)
	{
		runner = start;
	}
	else 
	{ 
		runner = me +1;
	}
	while (0 != *runner)
	{
		
		if ( runner == end )
		{
			runner = start;
		}
		else
		{
			++runner;
		}
	}
	
	return runner;
}

/* Printing BillBoard */

void ArrPrint (int *arr, size_t size_arr)
{	
	size_t i = size_arr;
	printf("Joseph billboard : [ ");
	for (i = 0 ; i<size_arr; ++i)
	{
		printf("%d, ", arr[i]);
	}
	printf("]\n");
}
