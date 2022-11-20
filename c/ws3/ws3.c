#include <stdio.h>       /* for main function       */
#include <stddef.h>     /* for size_t             */	
#include <stdlib.h>    /* for dynamic allocation */
#include <assert.h>   /* 	asserts        */

/* defining a head the amount of players in josephus */
#define SIZE 100
/* defining last index of environ, to compile without magic numbers */
#define LAST_INDEX_OF_ENV 1
/* ERROR DEFINE */
#define ERROR 1
/* importing environ */
extern char **environ;
/* Joespush problem                                 */
int Joseph(int *arr, size_t size_arr);
/* Finding the next person to kill or give sword   */
int *FindNextAlive(int *start, int *me, size_t size_arr);
/* printing the indexes with the winner inside      */
void ArrPrint (int *arr, size_t size_arr);
/* 	beggining of buffer build  	          */
void Buffer();
/* 	function for sizing environ 	         */
size_t EnvironSize();
/*      building the matrix  	                */
void BuildMatrix(int arr_size);
/* 	sizing the strings of pointers	       */
size_t StrLen(const char *str);
/* 	used to copy the environ to buff        */
char *StrCpy(char *destination, const char *source);
void ToLower(char *ch);
/*  printing the buffer content lowercase       */
void PrintENV(char **buffer);


int main()
{
	/* variables for joes */
	size_t joes_size =0;
	int arr[SIZE];
	
	while (joes_size<SIZE)
	{
	  arr[joes_size] = 0;
	  ++joes_size;
  	}
  
	printf("The winnder is at place : %d\n", (Joseph(arr , SIZE-1)+1));
	ArrPrint(arr, SIZE);
	
	Buffer();
	
	return (0);
			
}

/******************Josephus game begins*****************************/
int Joseph(int *arr, size_t size_arr)
{
	int *start = arr;
	int *me = arr;
	size_t moves = 0 ;
	int *alive = NULL;
	
	while ( size_arr != moves)
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


/*****************************************************************************/
/*****************BUFFER FUNCTION********************************************/	


void Buffer()
{	
	size_t envp_size = EnvironSize();
	BuildMatrix(envp_size);

}
size_t EnvironSize()
{
	size_t i;
	size_t counter = 0;  
	for (i = 0 ; NULL != environ[i]; ++i)
	{
		++counter;
	}
	
	return (counter+1);
}

void BuildMatrix(int arr_size)
{
	size_t i = 0; 
	size_t j = 0;
	size_t count= 0 ;
	char **buff =(char **)malloc((arr_size)*sizeof(char *));
	
	if (NULL == buff)
	{
		free(buff);
	}
	
	for (i = 0 ; NULL != environ[i]; ++i)
	{
		buff[i] = (char *)malloc((StrLen(environ[i])+LAST_INDEX_OF_ENV)*sizeof(char));
		++count;
	}
	
	buff[count] = NULL; 
	
	for (j = 0 ; NULL != environ[j]; ++j)
	{
		StrCpy(buff[j], environ[j]);
	}

	PrintENV(buff);
	
	for (i = 0 ; NULL != environ[i]; ++i)
	{
		free(buff[i]);
	}
	
	free(buff);
	
}
	
size_t StrLen(const char *str)
{
	char *start = (char *)str;
	assert (NULL != str);
	while ('\0' != *str)
	{
		++str;
	}
	return (str - start);
}	
	
char *StrCpy(char *destination, const char *source)             
{
	 /* saving beginning of the string */
	char *head_str = destination;                          
	
	assert( NULL != destination );
	assert( NULL != source );
	
	do 
	{
		*destination = *source;
		++destination;
	}while('\0' != *source++);
	
	return (head_str);
}

void PrintENV(char **buffer)
{
     int i = 0;
     while(NULL != buffer[i])
     { 
     	ToLower(buffer[i]);        
     	printf("%s\n", buffer[i]);
     	++i; 
     } 
}


void ToLower(char *ch)
{

	while ('\0' != *ch)
	{
			*ch |= 32;
			++ch;
	}
		
}



