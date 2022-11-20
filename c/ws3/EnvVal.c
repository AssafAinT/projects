#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>

extern char **environ;

void Buffer();
void ToLower(char *ch);
size_t EnvironSize();
size_t StrLen(const char *str);
void BuildMatrix(int arr_size);
void PrintENV(char **buffer);
char *StrCpy(char *destination, const char *source);   

int main()
{
	Buffer();
	return (0);
	
}

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

void BuildMatrix(arr_size)
{
	size_t i = 0; 
	size_t j = 0;
	size_t count= 0 ;
	char **buff =(char **)malloc((arr_size)*sizeof(char *));
	
	for (i = 0 ; NULL != environ[i]; ++i)
	{
		buff[i] = (char *)malloc((StrLen(environ[i])+1)*sizeof(char));
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
	

void ToLower(char *ch)
{
	while ('\0' != *ch)
	{
		if('A' <=*ch  && 'Z' >=*ch) 
		{
			*ch += 32;
		}
		++ch;
	}
		
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

